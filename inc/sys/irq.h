#ifndef __CUTE_SYS_IRQ_H__
#define __CUTE_SYS_IRQ_H__

#include "sys/types.h"

void irq_init();
void irq_add_handler(int irq, void (*handler)(struct regs* r));
void irq_del_handler(int irq);

#endif //__CUTE_SYS_IRQ_H__
