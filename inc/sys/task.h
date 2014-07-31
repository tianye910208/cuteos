#ifndef __CUTE_SYS_TASK_H__
#define __CUTE_SYS_TASK_H__

#define MAX_TASKS 64

#include "def.h"


typedef enum {
	TASK_INIT,
	TASK_READY,
	TASK_RUNNING,
	TASK_WAIT,
	TASK_EVENT_WAIT,
	TASK_BLOCK,
	TASK_DELAY,
	TASK_TERMINATE
} TASK_STATE;

struct task
{
	int   tid;
	TASK_STATE state;
	void* stack;
	int   level;
	char  tname[20];
	void (*func) ( void );
};


extern TSS sys_task_state;
extern int sys_task_stack[1024];

extern int  curr_task_cnt;
extern int  curr_task_tid;
extern int* curr_task_sp;
extern int  next_task_tid;
extern struct task tasks[MAX_TASKS];

extern void task_init();

extern void task_switch();

extern int  task_create(void* stack, char* name, void (*func)(void), int level);
extern void task_destroy(int tid);

extern void* task_stack_init(void *start_addr, void *data, void *stack_top);


#endif
