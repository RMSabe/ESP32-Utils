#include "delay.h"
#include <stdint.h>
#include "rim/ets_sys.h"

void delay_us(uint32_t time_us)
{
  ets_delay_us(time_us);
  return;
}
