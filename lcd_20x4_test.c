/*
Example/Test for lcd_ctrl.h resource using a 20x4 LCD Display. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "driver/gpio.h"
#include "delay.h"
#include "lcd_ctrl.h"

lcd_t lcd1 = {
  .db4 = GPIO_NUM_14,
  .db5 = GPIO_NUM_15,
  .db6 = GPIO_NUM_16,
  .db7 = GPIO_NUM_17,
  .rs = GPIO_NUM_13,
  .e = GPIO_NUM_4,
  .n_char_per_line = 20,
  .n_lines = 4
};

uint8_t nbyte = 0;
char text[32];

void loop(void)
{
  sprintf(text, "%d  ", nbyte); //Byte range goes from 0 to 255. After 255 it goes back to 0. Use 2 whitespaces to erase the last two digits.
  lcd_set_cursor(&lcd1, 14, 0);
  lcd_print_text(&lcd1, text);
  delay_us(1000000);
  nbyte++;
  return;
}

void app_main(void)
{
  lcd_init(&lcd1);
  lcd_set_cursor(&lcd1, 0, 0);
  lcd_print_text(&lcd1, "This is line 0");
  lcd_set_cursor(&lcd1, 0, 1);
  lcd_print_text(&lcd1, "This is line 1");
  lcd_set_cursor(&lcd1, 0, 2);
  lcd_print_text(&lcd1, "This is line 2");
  lcd_set_cursor(&lcd1, 0, 3);
  lcd_print_text(&lcd1, "This is line 3");
  delay_us(5000000);
  
  lcd_clear(&lcd1);
  lcd_set_cursor(&lcd1, 0, 0);
  lcd_print_text(&lcd1, "Byte Counter: ");
  while(true) loop();
  
  return;
}
