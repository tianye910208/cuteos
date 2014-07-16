#include "sys/boot.h"
#include "sys/init.h"

struct multiboot_information* g_multiboot_info = 0;

void boot()
{
	gdt_init();
	idt_init();

	isr_init();
	irq_init();

	sys_init();
}
