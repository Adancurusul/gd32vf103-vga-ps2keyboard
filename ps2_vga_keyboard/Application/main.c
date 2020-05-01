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

	printf("into_loop \n");
/*
	show_char(0,1,'-');
		show_char(16,1,'-');
		show_char(16*2,1,'-');
		show_char(16*3,1,'-');
		show_char(16*4,1,'-');
		show_char(16*5,1,'m');
		show_char(16*6,1,'a');
		show_char(16*7,1,'t');
		show_char(16*8,1,'h');
		show_char(16*9,1,'b');
		show_char(16*10,1,'a');
		show_char(16*11,1,'s');
		show_char(16*12,1,'i');
		show_char(16*13,1,'c');
		show_char(16*14,1,'-');
		show_char(16*15,1,'-');
		show_char(16*16,1,'-');
		show_char(16*17,1,'-');
	show_char(0,30,'>');
	show_char(16,30,'P');
	show_char(16*2,30,'R');
	show_char(16*3,30,'I');
	show_char(16*4,30,'N');
	show_char(16*5,30,'T');
	show_char(16*6,30,' ');
	show_char(16*7,30,'"');
	show_char(16*8,30,'F');
	show_char(16*9,30,'a');
	show_char(16*10,30,'n');
	show_char(16*11,30,'t');
	show_char(16*12,30,'a');
	show_char(16*13,30,'s');
	show_char(16*14,30,'t');
	show_char(16*15,30,'i');
	show_char(16*16,30,'c');
	show_char(16*17,30,'"');

		//show_char(0,60,'>');
		show_char(16,60,'F');
		show_char(32,60,'a');
		show_char(48,60,'n');
				show_char(64,60,'t');
				show_char(16*5,60,'a');
				show_char(16*6,60,'s');
				show_char(16*7,60,'t');
				show_char(16*8,60,'i');
				show_char(16*9,60,'c');


				show_char(0,90,'>');
				show_char(16,90,'a');
				show_char(16*2,90,'=');
				show_char(16*3,90,' ');
				show_char(16*4,90,'s');
				show_char(16*5,90,'q');
				show_char(16*6,90,'r');
				show_char(16*7,90,'t');
				show_char(16*8,90,'(');
				show_char(16*9,90,'3');
				show_char(16*10,90,')');

				show_char(0,120,'>');
				show_char(16,120,'P');
				show_char(16*2,120,'R');
				show_char(16*3,120,'I');
				show_char(16*4,120,'N');
				show_char(16*5,120,'T');
				show_char(16*6,120,' ');
				show_char(16*7,120,'a');
				show_char(0,150,' ');
								show_char(16,150,'1');
								show_char(16*2,150,'.');
								show_char(16*3,150,'7');
								show_char(16*4,150,'3');
								show_char(16*5,150,'2');
								show_char(16*6,150,'0');
								show_char(16*7,150,'5');
								show_char(16*8,150,'1');
*/
	//for(int k = 1;k<300;k++){
	//	set_pixel(k,k);
	//	printf("giao\n");
	//}


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

