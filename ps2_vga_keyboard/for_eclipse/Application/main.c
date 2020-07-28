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


int main() {

 init_ps2_keyboard();

init_vga();
show_string(8,5,"hello");
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
 while (1 == 1) {
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

