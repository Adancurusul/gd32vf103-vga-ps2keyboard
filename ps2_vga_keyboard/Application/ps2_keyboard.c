#define PS2  1
#if PS2

#include "my_vga.h"
#include "main.h"
#include "lcd/lcd.h"
#include "ps2_keyboard.h"
#include "gd32vf103.h"
#include "gd32vf103_libopt.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

u32 ps2_bit_count = 11;
u32 into_count = 0;
u32 ps2_check = 0;
u32 ps2_data_now = 0;
u8 ps2_buffer[10];
u32 ps2_buffer_ptr;
u32 cursur_x = 1;
u32 cursur_y = 1;

void set_char(u8 c_now) {
	if (cursur_x > VGA_WIDTH - FONT_W) {
		cursur_x = 0;
		cursur_y += char_pixel_y;
	}
	if (cursur_y > VGA_HEIGHT - FONT_H) {
		cursur_x = 0;
		cursur_y = 0;
		vga_clear_screen();
	}

	if (c_now == enter) {
		cursur_x = 0;
		cursur_y += char_pixel_y;
	} else if (c_now == backspace) {
		if (cursur_x) {
			cursur_x -= char_pixel_x;
			clear_char(cursur_x, cursur_y);
		}

	} else {
		show_char(cursur_x, cursur_y, c_now);
		cursur_x += char_pixel_x;
	}

}

static u8 shifted[][2] = {

};
static u8 unshifted[][2] = { { 0x1c, 'a' }, { 0x32, 'b' }, { 0x21, 'c' }, {
		0x23, 'd' }, { 0x24, 'e' }, { 0x2b, 'f' }, { 0x34, 'g' }, { 0x33, 'h' },
		{ 0x43, 'i' }, { 0x3b, 'j' }, { 0x42, 'k' }, { 0x4b, 'l' },
		{ 0x3a, 'm' }, { 0x31, 'n' }, { 0x44, 'o' }, { 0x4d, 'p' },
		{ 0x15, 'q' }, { 0x2d, 'r' }, { 0x1b, 's' }, { 0x2c, 't' },
		{ 0x3c, 'u' }, { 0x2a, 'v' }, { 0x1d, 'w' }, { 0x22, 'x' },
		{ 0x35, 'y' }, { 0x1a, 'z' }, { 0x45, '0' }, { 0x16, '1' },
		{ 0x1e, '2' }, { 0x26, '3' }, { 0x25, '4' }, { 0x2e, '5' },
		{ 0x36, '6' }, { 0x3d, '7' }, { 0x3e, '8' }, { 0x46, '9' },
		{ 0x0e, '`' }, { 0x4e, '-' }, { 0x55, '=' }, { 0x5d, '\\' }, { 0x66,
				backspace }, { 0x29, ' ' }, { 0x54, '[' }, { 0x58, ']' }, {
				0x4c, ';' }, { 0x52, '\'' }, { 0x41, ',' }, { 0x49, '.' }, {
				0x4a, '/' }, { 0x0d, tab }, { 0x5a, enter },
//{0x58,caps},

		};
u8 scan_table(u8 code) {
	for (int i = 0; i < 43; i++) {
		if (code == unshifted[i][0]) {
			return unshifted[i][1];
		}
	}
	return 0;
}

u8 ps2_decode(u8 code) {
	if (code == 0xe0) {
		ext_status = true;
		return 0;
	}
	//u32 breakcode = ((code&0x80) !=0);
	if (code == 0xf0) {
		break_status = true;
		//printf("into\n");
		return 0;
	}
	//if(ext_status)
//printf("statusnow: break_status\n")
	if (break_status) { //into print
		break_status = 0;
		//printf("code %02x\n",code);
		u8 current_char = scan_table(code);
		return current_char;
		if (current_char != 0) {
			printf("%c", current_char);
			set_char(current_char);
		}
	}
	//if(!shift_status){

	//}

}
/*!
 \brief      uart0 init function
 \param[in]  none
 \param[out] none
 \retval     none
 */
void init_uart0(void) {
	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOA);
	/* enable USART clock */
	rcu_periph_clock_enable(RCU_USART0);

	/* connect port to USARTx_Tx */
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	/* connect port to USARTx_Rx */
	gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	/* USART configure */
	usart_deinit(USART0);
	usart_baudrate_set(USART0, 115200U);
	usart_word_length_set(USART0, USART_WL_8BIT);
	usart_stop_bit_set(USART0, USART_STB_1BIT);
	usart_parity_config(USART0, USART_PM_NONE);
	usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
	usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_enable(USART0);

	usart_interrupt_enable(USART0, USART_INT_RBNE);
}

int _put_char(int ch) {
	usart_data_transmit(USART0, (uint8_t) ch);
	while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET) {
	}

	return ch;
}

/*!
 \brief      ps2 keyboard init function
 \param[in]  none
 \param[out] none
 \retval     none
 */
void ps2_gpio_init(void) {
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOC);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_G);
	gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_B);
	gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_R);
	gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, PS2_CLK);
	gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, PS2_DATA);
	gpio_init(GPIOA, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, CLR_PIN);
	GPIO_BOP(GPIOA) = LED_B;
	GPIO_BOP(GPIOA) = LED_G;
	GPIO_BOP(GPIOC) = LED_R;
	//GPIO_BOP(GPIOA) = PS2_CLK;
}
/*!
 \brief      ps2 exti init function
 \param[in]  none
 \param[out] none
 \retval     none
 */

void ps2_exti_init(void) {
	eclic_irq_enable(EXTI0_IRQn, 3, 3);
	gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
	exti_init(EXTI_0, EXTI_INTERRUPT, EXTI_TRIG_FALLING); //configure key EXTI line
	exti_interrupt_flag_clear(EXTI_0);
}

/*!
 \brief      ps2 clk trigger function
 \param[in]  none
 \param[out] none
 \retval     none
 */
void EXTI0_IRQHandler(void) {
	u8 state_now;
	ps2_check = 0;
	if (RESET != exti_interrupt_flag_get(EXTI_0)) {
		state_now = gpio_input_bit_get(GPIOA, PS2_DATA);
		//printf("bitbefore%d\n",ps2_bit_count);

		if (ps2_bit_count == 11) {
			ps2_data_now = 0x00;
			if (0 == state_now) {
				ps2_bit_count--;
			}

		} else {
			if (ps2_bit_count < 11 && ps2_bit_count > 2) {
				ps2_data_now = (ps2_data_now >> 1);
				if (0 != state_now) {
					ps2_data_now = ps2_data_now + 0x80;
				}
				ps2_bit_count--;
			} else {
				if (ps2_bit_count == 2) {
					ps2_bit_count--;
				} else if (ps2_bit_count == 1) {
					ps2_bit_count = 11;
					//ps2_check=1;
					//ps2_data_now =(ps2_data_now<<1);
					//printf("code:%02x\n",ps2_data_now);
					u8 current_char = ps2_decode(ps2_data_now);
					if (current_char != 0) {
						printf("%c", current_char);
						set_char(current_char);
					}

				}
			}
		}
	}

	exti_interrupt_flag_clear(EXTI_0);
	//GPIO_BC(GPIOA) = LED_B;

	//printf("in handler:%d  now%d\n", ps2_bit_count,state_now );
}

void TIMER1_IRQHandler(void) {

	//gpio_bit_reset(GPIOA,GPIO_PIN_1);
	if (SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP)) {
		/* clear channel 0 interrupt bit */
		timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
		//led_toggle();
		if (ps2_check == 1) {
			ps2_bit_count = 11;
			//into_count = 0;
			ps2_data_now = 0;

		}
		ps2_check = 1;
	}
	//printf("clearok \n");
}

/*!
 \brief      timer config function
 \param[in]  timer num , interval ms
 \param[out] none
 \retval     none
 */
void timer_config(uint32_t timer_periph, uint32_t time_interval_ms) {
	timer_parameter_struct timer_initpara;

	switch (timer_periph) {
	case TIMER0:
		rcu_periph_clock_enable(RCU_TIMER0);
		break;
	case TIMER1:
		rcu_periph_clock_enable(RCU_TIMER1);
		break;
	case TIMER2:
		rcu_periph_clock_enable(RCU_TIMER2);
		break;
	case TIMER3:
		rcu_periph_clock_enable(RCU_TIMER3);
		break;
	case TIMER4:
		rcu_periph_clock_enable(RCU_TIMER4);
		break;
	case TIMER5:
		rcu_periph_clock_enable(RCU_TIMER5);
		break;
	case TIMER6:
		rcu_periph_clock_enable(RCU_TIMER6);
		break;
	default:
		break;
	}
	timer_deinit(timer_periph);
	timer_struct_para_init(&timer_initpara);
	timer_initpara.prescaler = 10799;	//108M/10800 = 10K Hz
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection = TIMER_COUNTER_UP;
	timer_initpara.period = (uint32_t) 10 * time_interval_ms;//(uint32_t)1000000U/time_interval_us;
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
	timer_init(timer_periph, &timer_initpara);

	timer_interrupt_enable(timer_periph, TIMER_INT_UP);	//update interrupt
	timer_enable(timer_periph);
}

/*!
 \brief      main function
 \param[in]  none
 \param[out] none
 \retval     none
 */
int init_ps2_keyboard(void) {
	eclic_global_interrupt_enable();
	ps2_gpio_init();
	ps2_exti_init();
	//Lcd_Init();

	init_uart0();
	eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);

	//eclic_irq_enable(TIMER1_IRQn, 1, 0);

	//timer_config(TIMER1, 200);	//.2s
	//LCD_Clear(BLACK);
	//BACK_COLOR = BLACK;

}

#endif
