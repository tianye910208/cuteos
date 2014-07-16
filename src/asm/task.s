global task_sw_int
extern curr_task_sp

task_sw_int:
	mov eax, curr_task_sp
	mov esp, [eax]


