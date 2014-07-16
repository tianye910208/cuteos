#ifndef __CUTE_DRV_SCREEN_H__
#define __CUTE_DRV_SCREEN_H__

void screen_init(void);

void screen_clear();
void screen_color(unsigned char forecolor, unsigned char backcolor);
void screen_putch(char c);
void screen_puts(const char *text);
void screen_puts_xy(const char *text, int new_x, int new_y);


#endif //__CUTE_DRV_SCREEN_H__
