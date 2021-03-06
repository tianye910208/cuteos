CC = gcc
LD = ld

CCFLAGS += -m32 -Werror -ffreestanding -nostdlib -I. -I./inc
LDFLAGS += -m elf_i386 -nostdlib

ASM_SRC = \
	src/asm/gdt.s \
	src/asm/idt.s \
	src/asm/isr.s \
	src/asm/irq.s \

SYS_SRC = \
	src/sys/boot.c \
	src/sys/init.c \
	src/sys/gdt.c \
	src/sys/idt.c \
	src/sys/isr.c \
	src/sys/irq.c \
	src/sys/io.c \
	src/sys/timer.c \
	src/sys/task.c \

DRV_SRC = \
	src/drv/screen.c \

LIB_SRC = \
    src/lib/string.c \

APP_SRC = \


OBJS = \
	 $(SYS_SRC:%.c=obj/%.o) \
	 $(ASM_SRC:%.s=obj/%.o) \
	 $(DRV_SRC:%.c=obj/%.o) \
	 $(LIB_SRC:%.c=obj/%.o) \
	 $(APP_SRC:%.c=obj/%.o) \

#######################################################################
# common modules
#######################################################################
all: bin/bootsect.bin bin/kernel_s.bin bin/kernel_m.bin

obj/%.o: %.s
	@echo [build] $<
	@mkdir -p $(@D)
	@nasm -f elf $< -o $@

obj/%.o: %.c
	@echo [build] $<
	@mkdir -p $(@D)
	@gcc $(CCFLAGS) -c $< -o $@
	
bin/bootsect.bin: src/asm/bootsect.s
	@echo [build] bootsect.bin
	@mkdir -p $(@D)
	@nasm -f bin $< -o $@

bin/kernel_s.bin: $(OBJS)
	@echo [link] kernel_s.bin
	@mkdir -p $(@D)
	@ld $(LDFLAGS) --oformat binary -T cfg/link_s.ld -o $@ $^

bin/kernel_m.bin: obj/src/asm/bootmult.o $(OBJS)
	@echo [link] kernel_m.bin
	@mkdir -p $(@D)
	@ld $(LDFLAGS) --oformat elf32-i386 -T cfg/link_m.ld -o $@ $^

clean:
	@rm -rf obj
	@rm -rf bin
	@rm -rf *.img
	@echo [clean] finish


IMAGE = floppy.img

image_s:bin/bootsect.bin bin/kernel_s.bin
	dd if=/dev/zero of=$(IMAGE) bs=512 count=2880
	dd if=bin/bootsect.bin of=$(IMAGE) bs=512 seek=0 conv=notrunc
	dd if=bin/kernel_s.bin of=$(IMAGE) bs=512 seek=1 conv=notrunc

image_m:bin/kernel_m.bin
	cp cfg/floppy.img floppy.img
	sudo /sbin/losetup /dev/loop0 floppy.img
	sudo mkdir mnt
	sudo mount /dev/loop0 mnt
	sudo cp bin/kernel_m.bin mnt/kernel.bin
	sudo mkdir -p mnt/boot/grub/
	sudo cp cfg/menu.lst mnt/boot/grub/menu.lst
	sudo umount /dev/loop0
	sudo /sbin/losetup -d /dev/loop0
	sudo rmdir mnt


qemu:
	qemu-system-i386 -fda $(IMAGE) -boot a


