#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "driver/gpio.h"
#include "delay.h"

#define LED_PIN GPIO_NUM_2
#define DELAY_TIME_US 250000 //250 ms

void loop(void)
{
  gpio_set_level(LED_PIN, true);
  delay_us(DELAY_TIME_US);
  gpio_set_level(LED_PIN, false);
  delay_us(DELAY_TIME_US);
  return;
}

void app_main(void)
{
  gpio_reset_pin(LED_PIN);
  gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
  
  while(true) loop();
  return;
}
