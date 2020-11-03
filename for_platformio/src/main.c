//#include "lcd/lcd.h"
#include "main.h"
#include "ps2_keyboard.h"
//#include "lcd/lcd.h"
//#include "ascii_2040.h"
 //#include "fatfs/tf_card.h"
#include "gd32vf103.h"
#include "gd32vf103_libopt.h"
#include "systick.h"
//#include "my_vga.h"
/*
#include <stdio.h>
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
*/
//typedef unsigned char u8;
//typedef unsigned int u16;
//typedef unsigned long u32;

/*
int _open(int status){return 0;}
int _kill(int status){return 0;}
int _getpid(int status){return 0;}
int _gettimeofday(int status){return 0;}
int _times(int status){return 0;}
*/

#define LED_PIN GPIO_PIN_13
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK RCU_GPIOC

void longan_led_init()
{
    /* enable the led clock */
    rcu_periph_clock_enable(LED_GPIO_CLK);
    /* configure led GPIO port */ 
    gpio_init(LED_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PIN);

    GPIO_BC(LED_GPIO_PORT) = LED_PIN;
}

void longan_led_on()
{
    GPIO_BOP(LED_GPIO_PORT) = LED_PIN;
}

void longan_led_off()
{
    GPIO_BC(LED_GPIO_PORT) = LED_PIN;
}



int main() {
longan_led_init();longan_led_off();
init_ps2_keyboard();

init_vga();
int k = 1;
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	//gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_G);
	//gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_B);
	//gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_R);FF
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_init(GPIOB, GPIO_MODE_IPU  , GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    gpio_bit_reset(GPIOB, GPIO_PIN_5);
    /*
show_string(k,1+FONT_H*0,"CRT  controller init ");
show_string(k,1+FONT_H*1,"  ");
show_string(k,1+FONT_H*2," ______     ______     ______   ______    ");
show_string(k,1+FONT_H*3,"/\\  ___\\   /\\  == \\   /\\__  _\\ /\\  ___\\   ");
show_string(k,1+FONT_H*4,"\\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ \\ \\ \\____ ");
show_string(k,1+FONT_H*5," \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\  \\ \\_____\\ ");
show_string(k,1+FONT_H*6,"  \\/_____/   \\/_/ /_/     \\/_/   \\/_____/ ");
show_string(k,1+FONT_H*7,"  ");
show_string(k,1+FONT_H*8,"Highspeed CRT controller :");
delay_1ms(1000);
show_string(k,1+FONT_H*9,"Buffer Size 39Kb");
delay_1ms(1000);
show_string(k,1+FONT_H*10,"    800*600@58Hz");
delay_1ms(1000);
show_string(k,1+FONT_H*11,"vga init finished");
delay_1ms(500);
show_string(k,1+FONT_H*12,"Ready to Reset...");
delay_1ms(10000);
vga_clear_screen();
delay_1ms(1000);
show_string(k,1+FONT_H*0,"  ,---.     ,--.               ");    
show_string(k,1+FONT_H*1," /  O  \\  ,-|  | ,- -,--.,--,--,  ");    
show_string(k,1+FONT_H*2,"|  .-.  |' .-. |' ,-.  ||      \\     "); 
show_string(k,1+FONT_H*3,"|  | |  |\\ `-' |\\ '-'  ||  ||  |      "); 
show_string(k,1+FONT_H*4,"`--' `--' `---'  `--`--'`--''--'      ");
show_string(k,1+FONT_H*5,",-----.                  ,--.  ,--.                  ,--.               ");
show_string(k,1+FONT_H*6,"|  |) /_  ,---.  ,---. ,-'  '-.|  | ,---.  ,--,--. ,-|  | ,---. ,--.--. ");
show_string(k,1+FONT_H*7,"|  .-.  \\| .-. || .-. |'-.  .-'|  || .-. |' ,-.  |' .-. || .-. :|  .--' ");
show_string(k,1+FONT_H*8,"|  '--' /' '-' '' '-' '  |  |  |  |' '-' '\\ '-'  |\\ `-' |\\   --.|  |   ");
show_string(k,1+FONT_H*9,"`------'  `---'  `---'   `--'  `--' `---'  `--`--' `---'  `----'`--'    ");
show_string(k,1+FONT_H*10,"Adan Bootloader for RV/AT");
delay_1ms(1200);
show_string(k,1+FONT_H*11,"INITIAL COMPLETE...");
delay_1ms(1000);
show_string(k,1+FONT_H*12,"    CPU     :   PRV464 SXR @ 40MHZ");
delay_1ms(1000);
show_string(k,1+FONT_H*13,"                8K+8K L1    OK");
delay_1ms(1000);
show_string(k,1+FONT_H*14,"    MEMORY  :   64MBYTE     OK");
delay_1ms(1000);
show_string(k,1+FONT_H*15,"    IO CTRL :   IOP408      OK");
delay_1ms(1000);
show_string(k,1+FONT_H*16,"    SDIO    :   NONE / $Vendor $Volume");
delay_1ms(1000);
show_string(k,1+FONT_H*17,"    ETH     :   NO CONN / STATIC IP XXX.XXX.XXX.XXX / DHCP");
//show_string(1,1+FONT_H*18,"    FLASH   :   NOR/NAND $Volume");
delay_1ms(2000);

vga_clear_screen();
delay_1ms(1000);
longan_led_on();delay_1ms(1000);longan_led_off();

show_string(k,1+FONT_H*0, "  _____  _____  _____  _____   __      __   ");
show_string(k,1+FONT_H*1, " |  __ \\|_   _|/ ____|/ ____|  \\ \\    / /   ");
show_string(k,1+FONT_H*2, " | |__) | | | | (___ | |   _____\\ \\  / /    ");
show_string(k,1+FONT_H*3, " |  _  /  | |  \\___ \\| |  |______\\ \\/ /              _ ");
show_string(k,1+FONT_H*4, " | | \\ \\ _| |_ ____) | |____      \\  /              | |   ");
show_string(k,1+FONT_H*5, " |_|  \\_\\_____|_____/ \\_____|     _\\/__ _ __ ___  __| |   ");
show_string(k,1+FONT_H*6, "               | '_ \\ / _ \\ \\ /\\ / / _ \\ '__/ _ \\/ _` |    ");
show_string(k,1+FONT_H*7, "               | |_) | (_) \\ V  V /  __/ | |  __/ (_| |     ");
show_string(k,1+FONT_H*8, "               | .__/ \\___/ \\_/\\_/_\\___|_|  \\___|\\__,_|_______  ");
show_string(k,1+FONT_H*9, "               | |               | |                /\\|__   __| ");
show_string(k,1+FONT_H*10,"   ___ ___  _ _|_|__  _ __  _   _| |_ ___ _ __     /  \\  | |    ");
show_string(k,1+FONT_H*11,"  / __/ _ \\| '_ ` _ \\| '_ \\| | | | __/ _ \\ '__|   / /\\ \\ | |    ");
show_string(k,1+FONT_H*12," | (_| (_) | | | | | | |_) | |_| | ||  __/ |     / ____ \\| |    ");
show_string(k,1+FONT_H*13,"  \\___\\___/|_| |_| |_| .__/ \\__,_|\\__\\___|_|    /_/    \\_\\_|    ");
show_string(k,1+FONT_H*14,"                     | |                                        ");
show_string(k,1+FONT_H*15,"                     |_|    ");
show_string(k,1+FONT_H*16,"No boot device! Press <F10>to setup.Press <F12>to select boot device.");
*/


//show_char(20,20,'h');
/*
show_string(1,1,"......@@@@@@@@@@.....O@@@^.......,@@@/......,@@@^....,@@@@@...=@@@@@@@@@@@@@@");
show_string(1,1+FONT_H,"......@@@@@@@@@@@@...O@@@^....../@@@`....../@@@...../@@@@@@^..@@@@@@@@@@@@@@ ");
show_string(1,1+FONT_H*2,".....@@@/..../@@@/...O@@@^.....O@OO   ...,@@@^....*@@@@@@@@`......=@@@/..   ");
show_string(1,1+FONT_H*3,"....@@@@..../@@@/....O@@@^...,@@@/   .../@@@...../@@@..@@@@^.....,@@@@...   ");
show_string(1,1+FONT_H*4,".../@@@@@@@@@@/......O@@@*..=@@O`   ..,@@@^...../@@@...@@@@^.....@@@@^... ");
show_string(1,1+FONT_H*5,"..=@@@@@@@@@\........O@@@*./@@O. ..../@@@.....,@@@@....@@@@^..../@@@/....  ");
show_string(1,1+FONT_H*6,"..@@@@...@@@@^.......O@@O*O@@/.....,@@@`...../@@@@@@@@@@@@@^...,@@@@..... ");
show_string(1,1+FONT_H*7,"./@@@^...=@@@@`......O@@O@@O`...../@@/.....,@@@@`*....*@@@@^...@@@@^.....");
show_string(1,1+FONT_H*8,"/@@@/.....@@@@@......O@@@@/......@@@`.....=@@@@........@@@@^..=@@@^......");
*/
/*


 const char lua_test[] = {//执行的lua程序
		 "print(\"Hello,I am lua!\\n--this is newline printf\")\n"
 };


     lua_State *L = NULL;

     L =luaL_newstate();  //创建lua状态机
     if(L == NULL)
     {
         printf("LUA ERR! \n");
         while(1){};//没进入则死循环
     }
     //luaL_openlibs(L);//注册库函数
    luaopen_base(L); //启用Lua基础库
     luaL_dostring(L, lua_test);//执行lua
     lua_close(L);
     printf("LUA END \n");
 //printf("ready \n");
 //printf("ready \n");

*/
int flag_on = 0;
 while (1 == 1) {
     if(!gpio_input_bit_get(GPIOB,GPIO_PIN_7)&&flag_on==0){
gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_bit_set(GPIOB, GPIO_PIN_9);
    gpio_bit_set(GPIOB, GPIO_PIN_8);
    flag_on=1;
     }
     else if(!gpio_input_bit_get(GPIOB,GPIO_PIN_7)&&flag_on==1){
         gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_bit_reset(GPIOB, GPIO_PIN_9);
    gpio_bit_reset(GPIOB, GPIO_PIN_8);
     flag_on=0;
     };
     delay_1ms(200);
  //printf("into_loop\n");

//delay_1ms(100);
//int a = spi_i2s_flag_get(SPI0,I2S_FLAG_TBE);
//if(a){
// printf("yes\n");

//}
//else{

 //delay_1ms(100);
 //gpio_bit_set(GPIOA,GPIO_PIN_1);
}
}

