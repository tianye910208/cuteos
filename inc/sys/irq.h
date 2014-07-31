#ifndef __CUTE_SYS_IRQ_H__
#define __CUTE_SYS_IRQ_H__

#include "sys/def.h"

extern void irq_init();
extern void irq_add_handler(int irq, void (*handler)(REG* r));
extern void irq_del_handler(int irq);

#endif //__CUTE_SYS_IRQ_H__
