/**
  *****************************************************************************
	RTOS - 7Segment,Relay Project
  * @file    main.c
  * @author  Mete Sepetcioglu 
  * @version v.0.0.0.1
  * @brief   Main program body
	* @project RTOS application with STM32F745ZGT6. 
  ******************************************************************************/
#include "stm32f7xx_hal.h"
#include "MCU_Config.h"
#include "SevenSegmentDisplay_Driver.h"
#include "button_relay_driver.h"

#ifdef _RTE_
#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  // when RTE component CMSIS RTOS2 is used
#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif

#ifdef RTE_CMSIS_RTOS2_RTX5
/**
  * Override default HAL_GetTick function
  */
void GPIOPinConfig(void);

uint32_t HAL_GetTick (void) {
  static uint32_t ticks = 0U;
         uint32_t i;

  if (osKernelGetState () == osKernelRunning) {
    return ((uint32_t)osKernelGetTickCount ());
  }

  /* If Kernel is not running wait approximately 1 ms then increment 
     and return auxiliary tick counter value */
  for (i = (SystemCoreClock >> 14U); i > 0U; i--) {
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
  }
  return ++ticks;
}
#endif


//int sayac = 0;
//int secondCounter = 0;

int main(void)
{
//MCU functions
	  MPU_Config();
	  CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();
	  
	  DSConfig(); 
	  InitLEDs();
	  PinInit();
	  osKernelInitialize();
	  StartThreads();
	  osKernelStart();
  	
    while (1)
    {	
//			sayac++;
//			if(sayac == 50)
//			{
//				secondCounter++;
//				sayac = 0;
//			}
//			twoDigitNumber(secondCounter);
//			DS1(8);
//			DS2(1);
//			
    }
}



