//#include "lcd/lcd.h"
#include "main.h"
#include "ps2_keyboard.h"
//#include "lcd/lcd.h"
//#include "ascii_2040.h"
#include "gd32vf103.h"
#include "gd32vf103_libopt.h"
#include "systick.h"
#include "my_vga.h"
#include <stdio.h>

//typedef unsigned char u8;
//typedef unsigned int u16;
//typedef unsigned long u32;



int main() {

	init_ps2_keyboard();



	init_vga();

	printf("into_loop\n");
	while (1 == 1) {
		//printf("into_loop\n");

//delay_1ms(100);
//int a = spi_i2s_flag_get(SPI0,I2S_FLAG_TBE);
//if(a){
//	printf("yes\n");

//}
//else{

	//delay_1ms(100);
	//gpio_bit_set(GPIOA,GPIO_PIN_1);
}
}

