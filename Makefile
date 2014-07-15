CC = gcc
LD = ld

CCFLAGS += -m32 -Werror -ffreestanding -nostdlib -I. -I./inc
LDFLAGS += -m elf_i386 -nostdlib

KERN_OBJS = \
	src/sys/boot.o \
	src/sys/init.o

LIB_OBJS = \
	src/lib/string.o

APP_OBJS = \


ALL_OBJS =  $(KERN_OBJS) $(LIB_OBJS) $(APP_OBJS)

#######################################################################
# common modules
#######################################################################
all: bin/bootsect.bin bin/kernel_s.bin bin/kernel_m.bin

%.o:%.s
	nasm -f elf $< -o $@

%.o:%.c
	gcc $(CCFLAGS) -c $< -o $@
	
bin/bootsect.bin: src/sys/bootsect.s
	nasm -f bin $< -o $@

bin/kernel_s.bin: $(ALL_OBJS)
	ld $(LDFLAGS) --oformat binary -T cfg/link_s.ld -o $@ $^

bin/kernel_m.bin: src/sys/bootmult.o $(ALL_OBJS)
	ld $(LDFLAGS) --oformat elf32-i386 -T cfg/link_m.ld -o $@ $^

clean:
	rm -f $(ALL_OBJS)
	rm -f bin/*
	rm -f *.o *.bin *.img


IMAGE = floppy.img

image_s:bin/bootsect.bin bin/kernel_s.bin
	dd if=/dev/zero of=$(IMAGE) bs=512 count=2880
	dd if=bin/bootsect.bin of=$(IMAGE) bs=512 seek=0 conv=notrunc
	dd if=bin/kernel_s.bin of=$(IMAGE) bs=512 seek=1 conv=notrunc

qemu:
	qemu-system-i386 -fda $(IMAGE) -boot a


