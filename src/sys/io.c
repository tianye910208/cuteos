#include "sys/io.h"

unsigned char ioread8(unsigned short port)
{
	unsigned char v;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (v) : "dN" (port));
	return v;
}

unsigned short ioread16(unsigned short port)
{
	unsigned short v;
	__asm__ __volatile__ ("inw %1, %0" : "=a" (v) : "d" (port));
	return v;
}

unsigned int ioread32(unsigned short port)
{
	unsigned int v;
	__asm__ __volatile__ ("inl %1, %0" : "=a" (v) : "d" (port));
	return v;
}


void iowrite8(unsigned short port, unsigned char v)
{
	__asm__ __volatile__ ("outb %0, %1" : : "a" (v), "dN" (port));
}

void iowrite16(unsigned short port, unsigned short v)
{
	__asm__ __volatile__ ("outw %0, %1" : : "a" (v), "d" (port));
}

void iowrite32(unsigned short port, unsigned int v)
{
	__asm__ __volatile__ ("outl %0, %1" : : "a" (v), "d" (port));
}
