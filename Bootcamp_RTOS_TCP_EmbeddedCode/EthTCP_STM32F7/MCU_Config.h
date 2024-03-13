
	#ifndef __MCU_CONFIG_H
	#define __MCU_CONFIG_H
	
	#include "stm32f7xx_hal.h"
	#include "main.h"
	
	#define LED1_Port GPIOF
	#define LED2_Port GPIOF
	#define LED3_Port GPIOF
	#define LED4_Port GPIOF

	#define LED1_Pin GPIO_PIN_2
	#define LED2_Pin GPIO_PIN_3
	#define LED3_Pin GPIO_PIN_4
	#define LED4_Pin GPIO_PIN_5

	#define LED1_ON HAL_GPIO_WritePin(LED1_Port, LED1_Pin, GPIO_PIN_SET)
	#define LED2_ON HAL_GPIO_WritePin(LED2_Port, LED2_Pin, GPIO_PIN_SET)
	#define LED3_ON HAL_GPIO_WritePin(LED3_Port, LED3_Pin, GPIO_PIN_SET)
	#define LED4_ON HAL_GPIO_WritePin(LED4_Port, LED4_Pin, GPIO_PIN_SET)

	#define LED1_OFF HAL_GPIO_WritePin(LED1_Port, LED1_Pin, GPIO_PIN_RESET)
	#define LED2_OFF HAL_GPIO_WritePin(LED2_Port, LED2_Pin, GPIO_PIN_RESET)
	#define LED3_OFF HAL_GPIO_WritePin(LED3_Port, LED3_Pin, GPIO_PIN_RESET)
	#define LED4_OFF HAL_GPIO_WritePin(LED4_Port, LED4_Pin, GPIO_PIN_RESET)

	#define LED1_TOGGLE HAL_GPIO_TogglePin(LED1_Port, LED1_Pin)
	#define LED2_TOGGLE HAL_GPIO_TogglePin(LED2_Port, LED2_Pin)
	#define LED3_TOGGLE HAL_GPIO_TogglePin(LED3_Port, LED3_Pin)
	#define LED4_TOGGLE HAL_GPIO_TogglePin(LED4_Port, LED4_Pin)
	
	#define RELAY_ON HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET)
	#define RELAY_OFF HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET)

  #define RELAY_STATE HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12) //RETURN 0-1
	
	 void LED_RELAY_Init(void);	 
   void Error_Handler(void);
   void CPU_CACHE_Enable(void);	
   void SystemClock_Config(void);
   void MPU_Config(void);	 
   void DeviceInitialize(void);
	#endif

