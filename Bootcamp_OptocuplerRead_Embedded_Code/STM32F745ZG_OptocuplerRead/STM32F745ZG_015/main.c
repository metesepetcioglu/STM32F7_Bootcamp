/**
  *****************************************************************************
	ID Switch Read Project
  * @file    main.c
  * @author  Mete Sepetcioglu 
  * @version v.0.0.0.1
  * @brief   Main program body
	* @project Optocoupler Read application with STM32F745ZGT6. 
  ******************************************************************************/
#include "stm32f7xx_hal.h"
#include "interrupt_driver.h"
#include "MCU_Config.h"

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

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

int main(void)
{
//MCU functions
	  MPU_Config();
	  CPU_CACHE_Enable();
    HAL_Init();
    SystemClock_Config();
   
//interrupt_driver function	
  	OptocuplerInit();
	
	  
    while (1)
    {
			
    }
}



