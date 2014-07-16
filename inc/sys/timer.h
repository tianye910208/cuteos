#ifndef __CUTE_SYS_TIMER_H__
#define __CUTE_SYS_TIMER_H__

void timer_init();
void timer_func();

unsigned int timer_ticks();
void timer_sleep(int tick);


#endif //__CUTE_SYS_TIMER_H__
