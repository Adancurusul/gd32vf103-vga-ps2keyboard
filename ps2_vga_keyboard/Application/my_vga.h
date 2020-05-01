/*
 * my_vga.h
 *
 *  Created on: 2020年4月25日
 *      Author: User
 */

#ifndef APPLICATION_MY_VGA_H_
#define APPLICATION_MY_VGA_H_
#include "main.h"
#include "gd32vf103_libopt.h"
#define FONT_SIZE 1608
void init_vga();
#if FONT_SIZE ==2040
#define FONT_W 35
#define FONT_H 40
#define PARAM_W 3
#define PARAM_WHOLE 120

#elif FONT_SIZE==2416
#define FONT_W 16
#define FONT_H 30
#define PARAM_W 2
#define PARAM_WHOLE 48

#elif FONT_SIZE==1608
#define FONT_W 8
#define FONT_H 16
#define FONT_HSPACE 4
#define PARAM_W 1
#define PARAM_WHOLE 16


#endif
void vga_clear_screen(void);
void show_char(u16 x, u16 y, u8 ch);
void clear_char(u16 x, u16 y);
void set_sursor(u16 x, u16 y);
void set_pixel(u16 x, u16 y);

#endif /* APPLICATION_MY_VGA_H_ */
