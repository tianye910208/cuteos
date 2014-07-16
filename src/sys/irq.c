#include "sys/types.h"
#include "sys/init.h"
#include "sys/io.h"

//IRQ handlers
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

//IRQ routines
void* irq_routines[16] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};


void irq_set_handler(int irq, void (*handler)(struct regs* r))
{
	irq_routines[irq] = handler;
}


void irq_unset_handler(int irq)
{
	irq_routines[irq] = 0;
}


void irq_remap(void)
{
	//Tell PIC to remap IRQs
	iowrite8(0x20, 0x11);
	iowrite8(0xA0, 0x11);
	iowrite8(0x21, 0x20);
	iowrite8(0xA1, 0x28);
	iowrite8(0x21, 0x04);
	iowrite8(0xA1, 0x02);
	iowrite8(0x21, 0x01);
	iowrite8(0xA1, 0x01);
	iowrite8(0x21, 0x0);
	iowrite8(0xA1, 0x0);
}


void irq_init()
{
	//Remap IRQs
	irq_remap();

	//Add IRQs into IDT
	idt_set(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set(47, (unsigned)irq15, 0x08, 0x8E);
}


void irq_handler(struct regs* r)
{
	//Handler pointer
	void (*handler)(struct regs* r);

	//Find handler and call it
	handler = irq_routines[r->int_no - 32];
	if (handler)
		handler(r);

	//Send EOI to slave controller for IRQs 8-15
	if (r->int_no >= 40)
		iowrite8(0xA0, 0x20);

	//Send EOI to master controller
	iowrite8(0x20, 0x20);
}
