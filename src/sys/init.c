#include "sys/init.h"
#include "sys/timer.h"


void sys_init()
{

	screen_puts("timer init...\n");
	timer_init();


	for(;;)
	{
		timer_sleep(10);
		screen_puts("*");
	}
}
