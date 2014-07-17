global task_sw_int
extern curr_task_sp

task_sw_int:
	mov eax, curr_task_sp
	mov esp, [eax]

	pop gs
	pop fs
	pop es
	pop ds

	mov ax, [esp + 32]
	cmp ax, 0x00ff
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



