#ifndef __CUTE_SYS_TYPES_H__
#define __CUTE_SYS_TYPES_H__

#define bool  _Bool
#define true  1
#define false 0

#undef  NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif



typedef int tid_t;
typedef int size_t;

/*  This defines what the stack looks like after an ISR was running */
struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;    
};


typedef char *va_list;
#define va_start(ap, p)		(ap = (char *) (&(p)+1))
#define va_arg(ap, type)	((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#endif //__CUTE_SYS_TYPES_H__
