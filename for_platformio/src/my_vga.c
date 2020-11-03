/*
 * my_vga.c
 *
 *  Created on: 2020年4月25日
 *      Author: User
 */

#include "my_vga.h"
#include "gd32vf103_libopt.h"
#include "main.h"
#if FONT_SIZE ==2040
#include "ascii_2040.h"
#elif FONT_SIZE==2416
#include "ascii_2416.h"
#elif FONT_SIZE==1608
#include "ascii_1608.h"

#endif

#define	VID_HSIZE		600/8	// Horizontal resolution (in bytes)
#define	VID_VSIZE		300		// Vertical resolution (in lines)

#define	VID_PIXELS_X	(VID_HSIZE * 8)
#define	VID_PIXELS_Y	VID_VSIZE
#define	VID_PIXELS_XR	(VID_PIXELS_X + 16)
#define	VID_HSIZE_R		(VID_HSIZE + 2)

/*****************************************
 * HSYNC ->B0 TIMER2CH2
 * VSYNC ->B6
 * GREEN ->A7 SPI0 MOSI
 *
 *****************************************/
#define ARRAYSIZE 75
u8 vga_buffer[VID_VSIZE][VID_HSIZE + 0];
//u8 vga_buffer[1][1];
u32 counter = 0;

static volatile u16 vline = 0;
static volatile u32 vflag = 0;
static volatile u32 vdraw = 0;
u32 timer_period = 0;
u32 dma_addr = (u32) &vga_buffer[0][0];
u16 channel1_pulse = 0, channel2_pulse = 0, channel3_pulse = 0;

int vi = 0, hi = 0, di = 0;

#define VGA_WIDTH 600
#define VGA_HEIGHT 300
#define PIXEL_INIT 0x80
u8 cursor_x = 0;
u8 cursor_y = 0;

void show_char(u16 x, u16 y, u8 ch);
void set_sursor(u16 x, u16 y);
void set_pixel(u16 x, u16 y);
void set_pixel(u16 x, u16 y) {
	//u16 t = x/8;
	//u16 n = x%8;
	vga_buffer[y][x / 8] |= PIXEL_INIT >> (x % 8);
}

u16 vga_x=8;
u16 vga_y=5;

void vga_print(u8 ch){
	if(ch=='\r'){
		vga_x=8;
		vga_y+=FONT_H;
		//    show_char(28,20,'k');
		vga_x+=FONT_W;
		return;
	}
	if(vga_x>VGA_WIDTH - FONT_W){vga_x=0;vga_y+=FONT_H;}
	if(vga_y>VGA_HEIGHT - FONT_H){vga_y=vga_x=0;vga_clear_screen();}
	show_char(vga_x,vga_y,ch);
	vga_x+=FONT_W;

}
void clear_char(u16 x, u16 y) {
	u8 temp, i, t = 0;
	u8 crosswise, lengthways;
	u16 x0 = x;
	if (!(x < VGA_WIDTH - FONT_W && x >= 0 && y < VGA_HEIGHT - FONT_H && y > 0)) {
		return;
	}
	u8 ch = ' ';
//printf("hello: %d\n",ch);
	cursor_x = x;
	cursor_y = y;
	u32 h = 9;

	for (lengthways = 0; lengthways < FONT_H; lengthways++) {

		for (crosswise = 0; crosswise < PARAM_W; crosswise++) {

			//temp = vga_ascii[(u16) ch * PARAM_WHOLE + crosswise + t * PARAM_W];
			//if(h%8)printf(" %02x ",temp);
			//else{ printf(" %02x \n",temp);}
			//h++;
			for (i = 0; i < 8; i++) {

					vga_buffer[y][x / 8] &= 0x00 >> (8 - x % 8);

				//else{
				//printf("0");
				//}
				//temp = temp >> 1;
				x++;
			}
		}
		y++;
		x = x0;
		t++;
	}
}
void show_string(u16 x,u16 y,const u8 *p)
{
    while(*p!='\0')
    {
        if(x>VGA_WIDTH - FONT_W){x=0;y+=FONT_H;}
        if(y>VGA_HEIGHT - FONT_H){y=x=0;vga_clear_screen();}
		//if(*p == '\n'){x = 0;y+=FONT_H;}
		
			show_char(x,y,*p);
        	x+=FONT_W;
        	p++;
		
        
    }
	//delay_1ms(200);//change!!!!!
}

void show_char(u16 x, u16 y, u8 ch) {
	u8 temp, i, t = 0;
	u8 crosswise, lengthways;
	u16 x0 = x;
	if (!(x < VGA_WIDTH - FONT_W && x >= 0 && y < VGA_HEIGHT - FONT_H && y > 0)) {
		return;
	}
	ch = ch - ' ';
//printf("hello: %d\n",ch);
	//cursor_x = x;
	//cursor_y = y;
	u32 h = 9;
//const unsigned char  vga_ascii[] =
	//printf("                  \n   next  \n   \n \n");

	for (lengthways = 0; lengthways < FONT_H; lengthways++) {

		for (crosswise = 0; crosswise < PARAM_W; crosswise++) {

			temp = vga_ascii[(u16) ch * PARAM_WHOLE + crosswise + t * PARAM_W];
			//if(h%8)printf(" %02x ",temp);
			//else{ printf(" %02x \n",temp);}
			//h++;
			vga_buffer[y][x / 8] = temp;
			x+=8;
			/*
			for (i = 0; i < 8; i++) {
				if (temp & 0x1) {
					vga_buffer[y][x / 8] |= PIXEL_INIT >> (8 - x % 8);
				printf("1");
				}
				else{
				vga_buffer[y][x/8] &= ~(PIXEL_INIT >> (8 - x % 8));
				printf("0");
				}
				temp = temp >> 1;
				x++;
			}*/
		}
		y++;
		// printf(" \n x now is: %d \n",x);
		x = x0;
		t++;
	}
	//printf(" \n x now is: %d \n",x);
}
void set_sursor(u16 x, u16 y) {
	if (x < VGA_WIDTH && x >= 0 && y < VGA_HEIGHT && y > 0) {
		cursor_x = x;
		cursor_y = y;
	}
}

/**
 \brief      configure the GPIO ports
 \param[in]  none
 \param[out] none
 \retval     none
 */
void vga_gpio_config(void) {

	rcu_periph_clock_enable(RCU_AF);

	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);	///////
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);	///////

	gpio_init(GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
	gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);//6
	gpio_bit_set(GPIOB, GPIO_PIN_12);//6
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,
	GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7);

	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_6);

}

/**
 \brief      configure the TIMER peripheral
 \param[in]  none
 \param[out] none
 \retval     none
 */
void vga_timer_config(void) {
	timer_oc_parameter_struct timer_ocinitpara;
	timer_parameter_struct timer_initpara;

	rcu_periph_clock_enable(RCU_TIMER2);
	//rcu_periph_clock_enable(RCU_TIMER3);
	timer_deinit(TIMER2);
	timer_struct_para_init(&timer_initpara);
	timer_initpara.prescaler = 0;
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = 3072;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER2, &timer_initpara);

	timer_channel_output_struct_para_init(&timer_ocinitpara);
	timer_ocinitpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocinitpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
	timer_ocinitpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
	timer_ocinitpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
	timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER2, TIMER_CH_2, &timer_ocinitpara);

	timer_channel_output_config(TIMER2, TIMER_CH_3, &timer_ocinitpara);

	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, 216);//216
	timer_channel_output_mode_config(TIMER2, TIMER_CH_2,
	TIMER_OC_MODE_PWM1);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_2,
	TIMER_OC_SHADOW_DISABLE);

	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 520);//520??400
	timer_channel_output_mode_config(TIMER2, TIMER_CH_3,
	TIMER_OC_MODE_PWM1);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_3,
	TIMER_OC_SHADOW_DISABLE);

	//timer_auto_reload_shadow_enable(TIMER2);
	//timer_master_slave_mode_config(TIMER3, TIMER_MASTER_SLAVE_MODE_ENABLE);
	timer_interrupt_flag_clear(TIMER2, TIMER_INT_CH2);
	timer_interrupt_flag_clear(TIMER2, TIMER_INT_CH3);
	timer_interrupt_enable(TIMER2,
	TIMER_INT_CH2 | TIMER_INT_CH3);

	timer_enable(TIMER2);

}

void vga_spi_config() {
	rcu_periph_clock_enable(RCU_SPI0);
	rcu_periph_clock_enable(RCU_DMA0);
	dma_parameter_struct dma_init_struct;

	/* SPI0 transmit dma config:DMA0-DMA_CH2 */
	dma_deinit(DMA0, DMA_CH2);
	dma_struct_para_init(&dma_init_struct);

	dma_init_struct.periph_addr = (uint32_t) &SPI_DATA(SPI0);
	dma_init_struct.memory_addr = (uint32_t) vga_buffer[0][0];
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
	dma_init_struct.priority = DMA_PRIORITY_LOW;
	dma_init_struct.number = ARRAYSIZE;
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_init(DMA0, DMA_CH2, &dma_init_struct);
	/* configure DMA mode */
	dma_circulation_disable(DMA0, DMA_CH2);
	dma_memory_to_memory_disable(DMA0, DMA_CH2);

	spi_parameter_struct spi_init_struct;
	/* deinitilize SPI and the parameters */
	//spi_i2s_deinit(SPI0);
	spi_i2s_deinit(SPI0);
	spi_struct_para_init(&spi_init_struct);

	/* SPI0 parameter config */
	spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
	spi_init_struct.device_mode = SPI_MASTER;
	spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
	spi_init_struct.nss = SPI_NSS_SOFT;
	spi_init_struct.prescale = SPI_PSC_4;
	spi_init_struct.endian = SPI_ENDIAN_MSB;
	spi_init(SPI0, &spi_init_struct);

	spi_enable(SPI0);

	/* DMA channel enable */

	//dma_channel_enable(DMA0, DMA_CH2);
	dma_interrupt_enable(DMA0, DMA_CH2, DMA_INT_FTF);
	dma_interrupt_flag_clear(DMA0, DMA_CH2, DMA_INT_FLAG_FTF);
	/* SPI DMA enable */
	spi_dma_enable(SPI0, SPI_DMA_TRANSMIT);

}

void TIMER2_IRQHandler(void) {
	//printf("into timer2irq\n");

	if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_CH2)) {
		/* clear channel 0 interrupt bit */
		//printf("giao");
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_CH2);

		if (counter == 2) {
			GPIO_BOP(GPIOB) = GPIO_PIN_12;//6
			counter += 1;
		} else if (counter == 24) {
			//GPIO_BOP(gpio_periph) = (uint32_t) pin;

			vflag = 1;
			counter += 1;
		} else if (counter == 625) {
			counter = 0;
			//GPIO_BC(GPIOB) = GPIO_PIN_15;
		} else if (counter == 0) {
			GPIO_BC(GPIOB) = GPIO_PIN_12;//6
			counter += 1;
			//printf("okse\n");
		} else {
			counter += 1;
		}

		//gd_eval_led_off(LED2);
		// printf("a\n");
	} else if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_FLAG_CH3)) {
		/* clear channel 1 interrupt bit */
		timer_interrupt_flag_clear(TIMER2, TIMER_INT_FLAG_CH3);
		//GPIO_BOP(GPIOB) = GPIO_PIN_15;
		if (vflag) {

			dma_channel_enable(DMA0, DMA_CH2);
			//dma_interrupt_flag_clear(DMA0, DMA_CH2, DMA_INT_FLAG_FTF);		//spi_enable(SPI0);
			//spi_dma_enable(SPI0, SPI_DMA_TRANSMIT);
			//dma_interrupt_enable(DMA0,DMA_CH4,DMA_INT_FTF);

			//printf("b\n");
		}
		//gd_eval_led_off(LED3);
		// printf("b\n");

	}
}
void DMA0_Channel2_IRQHandler() {
	if (dma_flag_get(DMA0, DMA_CH2, DMA_FLAG_FTF)) {
		di = 1;
		//printf("i\n");
		//spi_disable(SPI0);
		//spi_dma_disable(SPI0,SPI_DMA_TRANSMIT);
		dma_channel_disable(DMA0, DMA_CH2);
		dma_flag_clear(DMA0, DMA_CH2, DMA_FLAG_FTF);
		dma_interrupt_flag_clear(DMA0, DMA_CH2, DMA_INT_FLAG_FTF);

		vdraw++;
		if (vdraw == 2) {
			vdraw = 0;
			vline++;
			if (vline == VID_VSIZE) {
				vdraw = vline = vflag = 0;
				//dma_memory_address_config(DMA0, DMA_CH2,
				//(uint32_t) &vga_buffer[0][0]);
				dma_addr = (uint32_t) &vga_buffer[0][0];
			} else {
				dma_addr += ARRAYSIZE;
				//dma_memory_address_config(DMA0, DMA_CH2, dma_addr);
			}

		}
		dma_memory_address_config(DMA0, DMA_CH2, dma_addr);
	}

}

void vga_clear_screen(void) {
	u16 x, y;

	for (y = 0; y < VID_VSIZE; y++) {
		for (x = 0; x < ARRAYSIZE; x++) {
			vga_buffer[y][x]&= 0x00;
		}
	}
}

void vga_full_screen(void) {
	u16 x, y;

	for (y = 0; y < VID_VSIZE; y++) {
		for (x = 0; x < ARRAYSIZE; x++) {
			vga_buffer[y][x] |= 0x01;
		}
	}
}

void init_vga() {
	eclic_irq_enable(DMA0_Channel2_IRQn, 2, 2);
	eclic_irq_enable(TIMER2_IRQn, 1, 0);
	vga_gpio_config();
	//LCD_ShowString(0,0,"gpioinit",WHITE);
	vga_timer_config();
	//vga_timer_config_b();
	//vga_timer_test();
	//LCD_ShowString(20,20,"timerinit",WHITE);
	vga_spi_config();
	//spi_init_b();
	//LCD_ShowString(40,40,"spiinit",WHITE);
	vga_clear_screen();
}

