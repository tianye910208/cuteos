#ifndef __CUTE_SYS_DEF_H__
#define __CUTE_SYS_DEF_H__

#define bool  _Bool
#define true  1
#define false 0

#undef  NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif


/*  This defines what the stack looks like after an ISR was running */
typedef struct _s_regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;    
}REG;


typedef struct _s_tss {
	unsigned int    backlink;
	unsigned int    esp0;       /*  stack pointer to use during interrupt */
	unsigned int    ss0;        /*    "   segment  "  "    "        "     */
	unsigned int    esp1;
	unsigned int    ss1;
	unsigned int    esp2;
	unsigned int    ss2;
	unsigned int    cr3;
	unsigned int    eip;
	unsigned int    flags;

	unsigned int    eax;
	unsigned int    ecx;
	unsigned int    edx;
	unsigned int    ebx;

	unsigned int    esp;
	unsigned int    ebp;

	unsigned int    esi;
	unsigned int    edi;

	unsigned int    es;
	unsigned int    cs;
	unsigned int    ss;
	unsigned int    ds;
	unsigned int    fs;
	unsigned int    gs;

	unsigned int    ldt;

	unsigned short  trap;
	unsigned short  iomap; 
}TSS;



typedef char *va_list;
#define va_start(ap, p)		(ap = (char *) (&(p)+1))
#define va_arg(ap, type)	((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)
#endif



static inline void disable_int()
{
	__asm__  __volatile__ ("cli");
}

static inline void enable_int()
{
	__asm__  __volatile__ ("sti");
}

static inline void wait()
{
	__asm__ __volatile ("sti;hlt");
}

#endif //__CUTE_SYS_DEF_H__


