/**
  *****************************************************************************
	ID Switch Read Project
  * @file    main.c
  * @author  Mete Sepetcioglu 
  * @version v.0.0.0.1
  * @brief   Main program body
	* @project ID Switch application with STM32F745ZGT6. 
  ******************************************************************************/
	
#include "stm32f7xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "stm32f7xx_hal.h"              // Interrupt Hal Library
#include "id_switch_driver.h"           // ID Switch User Driver
#include "MCU_Config.h"                 // STM32F745ZGT6 Configuration Driver


int main(void)
{
	HAL_Init();   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	SystemClock_Config_Fonc();
//	extiConfigfonc();
//	Intterrupt_gpioConfigfonc();
	ID_Switch_Init();
	
	while(1)
	{
		uint8_t currentID = IDNUMBER; 
    delay(100);
	}
	
} //
