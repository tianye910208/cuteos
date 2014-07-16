#include "sys/types.h"
#include "sys/init.h"
#include "sys/timer.h"

static unsigned int _g_timer_ticks = 0;

void timer_init()
{
    /* Installs 'timer_func' to IRQ0 */
    irq_add_handler(0, timer_func);
    _g_timer_ticks = 0;
}

void timer_func(struct regs *r)
{
    _g_timer_ticks++;
}

unsigned int timer_ticks()
{
	return _g_timer_ticks;
}

void timer_sleep(int ticks)
{
    unsigned long eticks = _g_timer_ticks + ticks;
    while(_g_timer_ticks < eticks) ;
}


