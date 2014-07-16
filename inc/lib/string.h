#ifndef __STRING_H__
#define __STRING_H__


char *itoa (int val, int base);
int  strcmp(const char* str1, const char* str2);
void strcpy(char *s, char *t);
int  strlen(const char *str);

void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);

char *strtok(char * s,const char * ct);
char *strpbrk(const char * cs,const char * ct);
unsigned int strspn(const char *s, const char *accept);
unsigned long strtoul(const char *str, char **endptr, int requestedbase);

#endif
