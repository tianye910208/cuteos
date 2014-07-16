#include "lib/string.h"

char *itoa (int val, int base)
{
	int i ;
	static char _l_itoa_buf[32] = {0};
	if(val == 0){
		_l_itoa_buf[30] = '0';
		return &_l_itoa_buf[30];
	}

	for(i = 30; i ; --i, val /= base){
		_l_itoa_buf[i] = "0123456789abcdef"[val % base];
		if(val == 0)	break;
	}

	return &_l_itoa_buf[i+1];
}

int strcmp(const char* str1, const char* str2)
{
	int i = 0;
	while(str1[i]!=0 && str2[i]!=0 && str1[i]==str2[i])
		++i;

	return str1[i]-str2[i];
}

void strcpy(char *s, char *t)
{
	while((*s = *t) != '\0')
	{
		s++;
		t++;
	}
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}
