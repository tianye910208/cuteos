#include "sys/boot.h"
#include "sys/init.h"
#include "drv/screen.h"

struct multiboot_information* g_multiboot_info = 0;

void boot()
{
	screen_init();

	screen_puts("gdt init...\n");
	gdt_init();

	screen_puts("idt init...\n");
	idt_init();

	screen_puts("isr init...\n");
	isr_init();

	screen_puts("irq init...\n");
	irq_init();

	screen_puts("sys init...\n");
	sys_init();
}
