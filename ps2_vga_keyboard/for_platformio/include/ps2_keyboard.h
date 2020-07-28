#include "main.h"
#include "my_vga.h"
typedef struct{
	u32 code;
	u8 key;
}keys;
#define char_pixel_x  FONT_W
#define char_pixel_y FONT_H+FONT_HSPACE
#define true 1
#define false 0
#define char_invisible 0
#define caps char_invisible
#define tab '\t'
#define backspace '\b'
#define esc '\x1b'
#define enter '\r'
#define delete '\x7f'
#define LED_R GPIO_PIN_13
#define LED_G GPIO_PIN_1
#define LED_B GPIO_PIN_2
#define PS2_CLK GPIO_PIN_0
#define PS2_DATA GPIO_PIN_3
#define CLR_PIN GPIO_PIN_6
static u8 break_status=0,shift_status=0,ctrl_status=0,caps_status=0,ext_status=0;

int init_ps2_keyboard(void);
