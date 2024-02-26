#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include "stm32f7xx_hal.h"
#include <stdint.h>

void SystemClock_Config_Fonc(void);
void delay(uint32_t time);
void __GPIO_Init(void);


#endif /* */ 
