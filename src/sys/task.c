#include "sys/def.h"
#include "sys/task.h"
#include "lib/string.h"


extern void task_sw_int();


int curr_task_cnt = 0;
int curr_task_tid = 0; //kernel main thread
int* curr_task_sp = 0;
int next_task_tid = 0;
struct task tasks[MAX_TASKS];

void task_init()
{
	tasks[0].tid = 0;
	strcpy(tasks[0].tname, "init");

	int i;
	for (i = 1; i < MAX_TASKS; i++) {
		tasks[i].tid = -1;
		tasks[i].state = TASK_TERMINATE;
	}

}

int task_create(void* stack, char* name, void (*func)(void), int level)
{
	disable_int();

	/* find a empty tid */
	int   ttid = 0;
	while(ttid < MAX_TASKS && tasks[ttid].tid != -1)
		ttid++;

	if(ttid < MAX_TASKS) 
	{
		curr_task_cnt++;
		tasks[ttid].tid = ttid;
		tasks[ttid].stack = task_stack_init(func, NULL, stack);
		tasks[ttid].state = TASK_WAIT;
		tasks[ttid].level= level;
		tasks[ttid].func = func;
		strcpy(tasks[ttid].tname, name);
	}else
	{
		ttid = -1;
	}

	enable_int();

	return ttid;
}

void task_destroy(int tid)
{
	curr_task_cnt--;

	tasks[tid].tid = -1;
	tasks[tid].tname[0] = '\0';
	tasks[tid].state = TASK_TERMINATE;
	tasks[tid].stack = NULL;
	tasks[tid].func = NULL;
}


void* task_stack_init(void *start_addr, void *data, void *stack_top)
{
	unsigned long *pstk = stack_top;

	/* Simulate call to function with argument */
	*pstk-- = (unsigned long)data;
	/* return address */
	*pstk-- = (unsigned long)start_addr;
	*pstk-- = 0x000000ff;	/* err_code  */
	*pstk-- = 0x000000ff;	/* int_no */

	*pstk-- = 0xAAAAAAAA;	/* EAX = 0xAAAAAAAA */
	*pstk-- = 0xCCCCCCCC;	/* ECX = 0xCCCCCCCC */
	*pstk-- = 0xDDDDDDDD;	/* EDX = 0xDDDDDDDD */
	*pstk-- = 0xBBBBBBBB;	/* EBX = 0xBBBBBBBB */
	*pstk-- = 0x00000000;	/* ESP = 0x00000000 */
	*pstk-- = 0x11111111;	/* EBP = 0x11111111 */
	*pstk-- = 0x22222222;	/* ESI = 0x22222222 */
	*pstk-- = 0x33333333;	/* EDI = 0x33333333 */

	*pstk-- = 0x00000010;	/* DS = 0x00000010 2nd GDT */
	*pstk-- = 0x00000010;	/* ES = 0x00000010 */
	*pstk-- = 0x00000010;	/* FS = 0x00000010 */
	*pstk   = 0x00000010;	/* GS = 0x00000010 */

	return (void*)pstk;
}




int task_pick_RR()
{
	int next = curr_task_tid;

	/* To find a valid task */
	do {
		next++;
	} while (tasks[next].tid < 0 && next < MAX_TASKS);

	if(next < MAX_TASKS)
		return next;
	else
		return 0;
}

/**
 * @brief pick up a ready task to run with specific scheduler
 */
void task_pick_next()
{
	next_task_tid = task_pick_RR();
}


void task_switch()
{
	/* suspend current task */
	current->state = TASK_WAIT;
	current->stack = curr_task_sp;

	task_pick_next();

	/* run continualy */
	if (curr_task_tid == next_task_tid)
	{
		tasks[curr_task_tid].state = TASK_RUNNING;
		return;
	}

	/* resume ready task */
	curr_task_tid = next_task_tid;
	current->state = TASK_RUNNING;
	curr_task_sp = tasks[curr_task_tid].stack;

	/* we are now in interrupt context */
	__asm__  __volatile__ (
		"jmp task_sw_int\n\t"
		);
}

