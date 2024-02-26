#ifndef __BUTTON_RELAY_DRIVER_
#define __BUTTON_RELAY_DRIVER_

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_exti.h"
#include "stm32f7xx_hal_gpio.h"
#include <stdint.h>

void PinInit(void);

extern volatile uint8_t button_flag;
#endif /*__BUTTON_RELAY_DRIVER_ */
