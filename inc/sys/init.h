#ifndef __CUTE_SYS_INIT_H__
#define __CUTE_SYS_INIT_H__

void gdt_init();
void gdt_set(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void idt_init();
void idt_set(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);


void sys_init();



#endif //__CUTE_SYS_INIT_H__
