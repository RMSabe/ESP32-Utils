#include "lcd_ctrl.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "driver/gpio.h"
#include "delay.h"

void lcd_print_bin(lcd_t *lcd, uint8_t bin)
{
  gpio_set_level(lcd->db7, (bin & 0x8));
  gpio_set_level(lcd->db6, (bin & 0x4));
  gpio_set_level(lcd->db5, (bin & 0x2));
  gpio_set_level(lcd->db4, (bin & 0x1));
  
  return;
}

void lcd_send_byte(lcd_t *lcd, bool reg, uint8_t byte)
{
  uint8_t high_bits = (byte >> 4);
  uint8_t low_bits = (byte & 0x0F);
  
  gpio_set_level(lcd->e, false);
  gpio_set_level(lcd->rs, reg);
  lcd_print_bin(lcd, high_bits);
  delay_us(1000);
  gpio_set_level(lcd->e, true);
  delay_us(1000);
  gpio_set_level(lcd->e, false);
  lcd_print_bin(lcd, low_bits);
  delay_us(1000);
  gpio_set_level(lcd->e, true);
  delay_us(1000);
  gpio_set_level(lcd->e, false);
  delay_us(1000);
  
  return;
}

void lcd_send_init_bits(lcd_t *lcd)
{
  gpio_set_level(lcd->e, false);
  gpio_set_level(lcd->rs, false);
  lcd_print_bin(lcd, 0x2);
  delay_us(1000);
  gpio_set_level(lcd->e, true);
  delay_us(1000);
  gpio_set_level(lcd->e, false);
  delay_us(2000);
  
  return;
}

void lcd_init(lcd_t *lcd)
{
  gpio_reset_pin(lcd->db4);
  gpio_reset_pin(lcd->db5);
  gpio_reset_pin(lcd->db6);
  gpio_reset_pin(lcd->db7);
  gpio_reset_pin(lcd->rs);
  gpio_reset_pin(lcd->e);
  
  gpio_set_direction(lcd->db4, GPIO_MODE_OUTPUT);
  gpio_set_direction(lcd->db5, GPIO_MODE_OUTPUT);
  gpio_set_direction(lcd->db6, GPIO_MODE_OUTPUT);
  gpio_set_direction(lcd->db7, GPIO_MODE_OUTPUT);
  gpio_set_direction(lcd->rs, GPIO_MODE_OUTPUT);
  gpio_set_direction(lcd->e, GPIO_MODE_OUTPUT);
  
  lcd_send_init_bits(lcd);
  lcd_send_byte(lcd, false, 0x28);
  lcd_send_byte(lcd, false, 0x01);
  lcd_send_byte(lcd, false, 0x0C);
  lcd_send_byte(lcd, false, 0x80);
  
  return;
}
