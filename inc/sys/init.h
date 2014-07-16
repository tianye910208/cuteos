#ifndef __CUTE_SYS_INIT_H__
#define __CUTE_SYS_INIT_H__

extern void gdt_init();
extern void gdt_set(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

extern void idt_init();
extern void idt_set(unsigned char num, unsigned long base, unsigned short selector, unsigned char flags);


extern void sys_init();



#endif //__CUTE_SYS_INIT_H__
