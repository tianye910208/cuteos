#include "sys/def.h"
#include "sys/init.h"
#include "sys/io.h"
#include "sys/timer.h"
#include "sys/task.h"

static unsigned int _g_timer_hz = 1000;
static unsigned int _g_timer_ticks = 0;

void timer_init()
{
    /* Installs 'timer_func' to IRQ0 */
    irq_add_handler(0, timer_func);

	_g_timer_hz	= 1000;
    _g_timer_ticks = 0;

	int dt = 1193180 / _g_timer_hz;

	//Set control byte
	iowrite8(0x43, 0x36);
	//Set divisor
	iowrite8(0x40, dt & 0xFF);
	iowrite8(0x40, dt >> 8);
}

void timer_func(struct regs *r)
{
    _g_timer_ticks++;
	task_switch();
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


