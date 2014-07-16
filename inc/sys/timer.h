#ifndef __CUTE_SYS_TIMER_H__
#define __CUTE_SYS_TIMER_H__

extern void timer_init();
extern void timer_func();

extern unsigned int timer_ticks();
extern void timer_sleep(int tick);


#endif //__CUTE_SYS_TIMER_H__
