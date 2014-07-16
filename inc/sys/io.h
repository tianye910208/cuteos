#ifndef __CUTE_SYS_IO_H__
#define __CUTE_SYS_IO_H__

extern unsigned char  ioread8(unsigned short port);
extern unsigned short ioread16(unsigned short port);
extern unsigned int   ioread32(unsigned short port );

extern void iowrite8(unsigned short port, unsigned char v);
extern void iowrite16(unsigned short port, unsigned short v);
extern void iowrite32(unsigned short port, unsigned int v);

#endif //__CUTE_SYS_IO_H__
