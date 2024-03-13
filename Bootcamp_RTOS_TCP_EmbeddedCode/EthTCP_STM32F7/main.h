
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "MCU_Config.h"
#include "cmsis_os2.h"                  // CMSIS RTOS header file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
#include "MCU_Config.h"


// Main stack size must be multiple of 8 Bytes
#define APP_MAIN_STK_SZ (1024U)

static uint64_t app_main_stk[APP_MAIN_STK_SZ / 8];
static const osThreadAttr_t app_main_attr = {
  .stack_mem  = &app_main_stk[0],
  .stack_size = sizeof(app_main_stk)
};

extern void app_main(void *argument);


#endif
