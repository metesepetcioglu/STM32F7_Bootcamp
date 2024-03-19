#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include "stm32f7xx_hal.h"
#include <stdint.h>


void SystemClock_Config(void);
void delay(uint32_t time);
void Error_Handler(void);
void TIM6_Config(void);
void DelayMilliseconds(uint32_t milliseconds);
void MPU_Config(void);
void SystemClock_Config(void);
void Error_Handler(void);
void CPU_CACHE_Enable(void);



#endif /*__MCU_CONFIG_H */
