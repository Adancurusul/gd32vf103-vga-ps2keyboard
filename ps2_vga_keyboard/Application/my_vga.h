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
#define FONT_SIZE 2040
void init_vga();
#if FONT_SIZE ==2040
#define FONT_W 40
#define FONT_H 40
#define PARAM_W 3
#define PARAM_WHOLE 120
#endif
void vga_clear_screen(void);
void show_char(u16 x, u16 y, u8 ch);
void clear_char(u16 x, u16 y);
void set_sursor(u16 x, u16 y);
void set_pixel(u16 x, u16 y);

#endif /* APPLICATION_MY_VGA_H_ */
