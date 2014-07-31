global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 32: IRQ0
irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub



; 33: IRQ1
irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_common_stub



; 34: IRQ2
irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_common_stub



; 35: IRQ3
irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_common_stub



; 36: IRQ4
irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_common_stub



; 37: IRQ5
irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_common_stub



; 38: IRQ6
irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_common_stub



; 39: IRQ7
irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_common_stub



; 40: IRQ8
irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_common_stub



; 41: IRQ9
irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_common_stub



; 42: IRQ10
irq10:
	cli
	push byte 0
	push byte 42
	jmp irq_common_stub



; 43: IRQ11
irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_common_stub



; 44: IRQ12
irq12:
	cli
	push byte 0
	push byte 44
	jmp irq_common_stub



; 45: IRQ13
irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_common_stub



; 46: IRQ14
irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_common_stub



; 47: IRQ15
irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_common_stub



extern irq_handler
extern task_switch
extern curr_task_sp

irq_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, ss
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov [curr_task_sp], esp

	mov eax, esp
	push eax


	call irq_handler

	pop eax

	mov esp, [curr_task_sp]

	pop gs
	pop fs
	pop es
	pop ds

	mov ax, [esp + 32]
	cmp ax, 0xff
	je ret_from_normal

ret_from_int:
	popa
	add esp, 8
	iret

ret_from_normal:
	popa
	add esp, 8
    sti
	ret
