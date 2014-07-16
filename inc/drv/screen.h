#ifndef __CUTE_DRV_SCREEN_H__
#define __CUTE_DRV_SCREEN_H__

extern void screen_init(void);
 
extern void screen_clear();
extern void screen_color(unsigned char forecolor, unsigned char backcolor);
extern void screen_putch(char c);
extern void screen_puts(const char *text);
extern void screen_puts_xy(const char *text, int new_x, int new_y);


#endif //__CUTE_DRV_SCREEN_H__
