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

st7920_t graphic_lcd = {
  .db0 = GPIO_NUM_18,
  .db1 = GPIO_NUM_19,
  .db2 = GPIO_NUM_21,
  .db3 = GPIO_NUM_22,
  .db4 = GPIO_NUM_14,
  .db5 = GPIO_NUM_15,
  .db6 = GPIO_NUM_16,
  .db7 = GPIO_NUM_17,
  .rs = GPIO_NUM_13,
  .e = GPIO_NUM_4
};

void draw_sine_wave(void)
{
  uint8_t cx = 0;
  uint8_t cy = 0;
  float x = 0.0f;
  float y = 0.0f;
  
  while(x < 6.28f)
  {
    y = sinf(x);
    cx = roundf(20*x);
    cy = 32 - roundf(28*y);
    st7920_load_graphic_buffer(&graphic_lcd, cx, cy);
    x += 0.01f;
  }
  
  st7920_paint_graphic_buffer(&graphic_lcd);
  return;
}

void draw_smiley_face(void) // (:
{
  uint8_t cx = 0;
  uint8_t cy = 0;
  float x = 0.0f;
  
  while(x <= 6.28f)
  {
    cx = 64 - roundf(28*cosf(x));
    cy = 32 - roundf(28*sinf(x));
    st7920_load_graphic_buffer(&graphic_lcd, cx, cy);
    x += 0.01f;
  }
  
  x = 3.4f;
  while(x <= 6.02f)
  {
    cx = 64 - roundf(18*cosf(x));
    cy = 34 - roundf(14*sinf(x));
    st7920_load_graphic_buffer(&graphic_lcd, cx, cy);
    x += 0.01f;
  }
  
  st7920_load_graphic_buffer(&graphic_lcd, 53, 22);
  st7920_load_graphic_buffer(&graphic_lcd, 53, 23);
  st7920_load_graphic_buffer(&graphic_lcd, 54, 22);
  st7920_load_graphic_buffer(&graphic_lcd, 54, 23);
  
  st7920_load_graphic_buffer(&graphic_lcd, 73, 22);
  st7920_load_graphic_buffer(&graphic_lcd, 73, 23);
  st7920_load_graphic_buffer(&graphic_lcd, 74, 22);
  st7920_load_graphic_buffer(&graphic_lcd, 74, 23);
  
  st7920_paint_graphic_buffer(&graphic_lcd);
  return;
}

void print_ascii_text(void)
{
  st7920_set_text_cursor(&graphic_lcd, 0, 0);
  st7920_print_text(&graphic_lcd, "This is line 0");
  st7920_set_text_cursor(&graphic_lcd, 0, 1);
  st7920_print_text(&graphic_lcd, "This is line 1");
  st7920_set_text_cursor(&graphic_lcd, 0, 2);
  st7920_print_text(&graphic_lcd, "This is line 2");
  st7920_set_text_cursor(&graphic_lcd, 0, 3);
  st7920_print_text(&graphic_lcd, "This is line 3");
  
  return;
}

void print_gb_text(void)
{
  uint16_t *text = (uint16_t[7]) {0xA5E9, 0xA5D5, 0xA5A1, 0xA5A8, 0xA5EB, 0xA4B5, 0xA4F3}; //This basically spells my name in Japanese Kana Characters.
  st7920_set_text_cursor(&graphic_lcd, 0, 0);
  st7920_print_spchar_text(&graphic_lcd, text, 7);
  return;
}

void loop(void)
{
  draw_sine_wave();
  delay_us(5000000);
  st7920_clear_graphic(&graphic_lcd);
  draw_smiley_face();
  delay_us(5000000);
  st7920_clear_graphic(&graphic_lcd);
  print_ascii_text();
  delay_us(5000000);
  st7920_clear_text(&graphic_lcd);
  print_gb_text();
  delay_us(5000000);
  st7920_clear_text(&graphic_lcd);
  return;
}

void app_main(void)
{
  st7920_init(&graphic_lcd);
  st7920_graphic_buffer_malloc(&graphic_lcd);
  
  while(true) loop();
  return;
}
