/*
PC IP Adress - 192.168.127.99
MCU IP Adress -192.168.127.123 - PORT 4001
*/

#include "main.h"													//Main header
#ifdef _RTE_
	#include "RTE_Components.h"             // Component selection
#endif
#ifdef RTE_CMSIS_RTOS2                  	// when RTE component CMSIS RTOS2 is used
	#include "cmsis_os2.h"                  // ::CMSIS:RTOS2
#endif


#ifdef RTE_CMSIS_RTOS2_RTX5
/**
  * Override default HAL_GetTick function
  */
uint32_t HAL_GetTick (void) 
{
  static uint32_t ticks = 0U;
         uint32_t i;

  if (osKernelGetState () == osKernelRunning) 
	{
    return ((uint32_t)osKernelGetTickCount ());
  }

  for (i = (SystemCoreClock >> 14U); i > 0U; i--) 
	{
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
    __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
  }
  return ++ticks;
}
#endif


int main(void)
{
	  DeviceInitialize();

		osKernelInitialize ();
		osThreadNew(app_main, NULL, &app_main_attr);
		osKernelStart();
	

  while (1)
	{


	}
}

