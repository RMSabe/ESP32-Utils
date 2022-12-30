//This is a resource to control the ST7920 Graphic LCD Controller.
//Notice that this code is meant to be used for the standard 128x64 pixel mapping Graphic LCD Screens.
//Different pixel mapping screens might not work properly with this code.

#ifndef ST7920_CTRL_H
#define ST7920_CTRL_H

#include <stdint.h>
#include "driver/gpio.h"

typedef enum {
	ST7920_DISPLAY_OFF = 0,
	ST7920_CURSOR_OFF,
	ST7920_CURSOR_ON,
	ST7920_CURSOR_BLINK
} st7920_display_mode_t;

typedef struct {
	gpio_num_t db0;
	gpio_num_t db1;
	gpio_num_t db2;
	gpio_num_t db3;
	gpio_num_t db4;
	gpio_num_t db5;
	gpio_num_t db6;
	gpio_num_t db7;
	gpio_num_t rs;
	gpio_num_t e;
} st7920_t;

void st7920_init(st7920_t *lcd);
void st7920_set_display_mode(st7920_t *lcd, st7920_display_mode_t display_mode);
void st7920_clear_graphic_buffer(void);
void st7920_load_graphic_buffer(uint8_t cx, uint8_t cy);
void st7920_paint_graphic_buffer(st7920_t *lcd);
void st7920_clear_graphic(st7920_t *lcd);
void st7920_clear_text(st7920_t *lcd);
void st7920_set_text_cursor(st7920_t *lcd, uint8_t cx, uint8_t cy); //Horizontal Cursor position counts for every 2 ASCII characters. Use whitespace to shift 1 ASCII characters.
void st7920_print_text(st7920_t *lcd, const char *text);
void st7920_print_spchar(st7920_t *lcd, const uint16_t spchar);
void st7920_print_spchar_text(st7920_t *lcd, const uint16_t *spchar_text, uint32_t length);
void st7920_clear_all(st7920_t *lcd);

#endif
