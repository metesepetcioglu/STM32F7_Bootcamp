/**
  *****************************************************************************
	ADC Driver Project
  * @file    main.c
  * @author  Mete Sepetcioglu 
  * @version v.0.0.0.1
  * @brief   Main program body
  * @project ADC Driver application with STM32F745ZGT6. 
  ******************************************************************************/
#include "stm32f7xx_hal.h"
#include "temperature_read_driver.h"
#include "MCU_Config.h"


int main(void)
{
 
	HAL_Init();
	SystemClock_Config_Fonc();
	__GPIO_Init();
	
	DMA_ADC_Init();
  	while(1)
	{

	}
}




