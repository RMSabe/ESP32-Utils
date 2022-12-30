/*
Example/Test for st7920_ctrl.h resource using a 128x64 Graphic LCD Display.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include "driver/gpio.h"

#include "delay.h"
#include "st7920_ctrl.h"

#define DELAY_TIME_US 4000000

st7920_t glcd = {
	.db0 = GPIO_NUM_18,
	.db1 = GPIO_NUM_19,
	.db2 = GPIO_NUM_22,
	.db3 = GPIO_NUM_23,
	.db4 = GPIO_NUM_14,
	.db5 = GPIO_NUM_15,
	.db6 = GPIO_NUM_16,
	.db7 = GPIO_NUM_17,
	.rs = GPIO_NUM_13,
	.e = GPIO_NUM_4
};

void proc_0(void) //Draw a sine wave
{
	uint8_t cx = 0;
	uint8_t cy = 0;
	float x = 0.0f;
	float y = 0.0f;

	while(x <= 6.28f)
	{
		y = sinf(x);
		cx = roundf(20*x);
		cy = 32 - roundf(28*y);
		st7920_load_graphic_buffer(cx, cy);
		x += 0.01f;
	}
	
	st7920_paint_graphic_buffer(&glcd);
	return;
}

void proc_1(void) //Draw a smiley face (:
{
	uint8_t cx = 0;
	uint8_t cy = 0;
	float x = 0.0f;

	while(x <= 6.28f)
	{
		cx = 64 - roundf(28*cosf(x));
		cy = 32 - roundf(28*sinf(x));
		st7920_load_graphic_buffer(cx, cy);
		x += 0.01f;
	}

	x = 3.4f;
	while(x <= 6.02f)
	{
		cx = 64 - roundf(18*cosf(x));
		cy = 34 - roundf(14*sinf(x));
		st7920_load_graphic_buffer(cx, cy);
		x += 0.01f;
	}

	st7920_load_graphic_buffer(53, 22);
	st7920_load_graphic_buffer(53, 23);
	st7920_load_graphic_buffer(54, 22);
	st7920_load_graphic_buffer(54, 23);

	st7920_load_graphic_buffer(73, 22);
	st7920_load_graphic_buffer(73, 23);
	st7920_load_graphic_buffer(74, 22);
	st7920_load_graphic_buffer(74, 23);

	st7920_paint_graphic_buffer(&glcd);
	return;
}

void proc_2(void) //Print some ASCII text
{
	st7920_set_text_cursor(&glcd, 0, 0);
	st7920_print_text(&glcd, "This is line 0");
	st7920_set_text_cursor(&glcd, 0, 1);
	st7920_print_text(&glcd, "This is line 1");
	st7920_set_text_cursor(&glcd, 0, 2);
	st7920_print_text(&glcd, "This is line 2");
	st7920_set_text_cursor(&glcd, 0, 3);
	st7920_print_text(&glcd, "This is line 3");

	return;
}

void proc_3(void) //Print some 16BIT GB character text
{
	const uint16_t text[7] = {0xA5E9, 0xA5D5, 0xA5A1, 0xA5A8, 0xA5EB, 0xA4B5, 0xA4F3}; //That's my name written in Japanese kana characters.
	st7920_set_text_cursor(&glcd, 0, 0);
	st7920_print_spchar_text(&glcd, text, 7);

	return;
}

void loop(void)
{
	proc_0();
	delay_us(DELAY_TIME_US);
	st7920_clear_graphic(&glcd);
	proc_1();
	delay_us(DELAY_TIME_US);
	st7920_clear_graphic(&glcd);
	proc_2();
	delay_us(DELAY_TIME_US);
	st7920_clear_text(&glcd);
	proc_3();
	delay_us(DELAY_TIME_US);
	st7920_clear_text(&glcd);

	return;
}

void app_main(void)
{
	st7920_init(&glcd);
	while(true) loop();

	return;
}
