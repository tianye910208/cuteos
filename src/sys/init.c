#include "sys/def.h"
#include "sys/init.h"
#include "sys/timer.h"
#include "sys/task.h"


int stacka[1024];
int stackb[1024];
void taska();
void taskb();

void sys_init()
{
	screen_puts("timer init...\n");
	timer_init();
	task_init();


	enable_int();


	task_create(stacka + 1024 - 1, "taska", taska, 0);
	task_create(stackb + 1024 - 1, "taskb", taskb, 0);

	while(true)
	{
		timer_sleep(800);
		screen_puts("O");
		//wait();
	}
}

void taska()
{
	while(true)
	{
		timer_sleep(800);
		screen_puts("A");
	}
}

void taskb()
{
	while(true)
	{
		timer_sleep(1100);
		screen_puts("B");
	}
}
