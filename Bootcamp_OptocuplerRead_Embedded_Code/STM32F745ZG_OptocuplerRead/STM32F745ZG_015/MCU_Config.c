#include "stm32f7xx_hal.h"
#include "MCU_Config.h"
#include "stm32f7xx.h"                  // Device header

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */

/*****************************************************************************************************/
/*****************************************************************************************************/
 void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
		RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
     //   Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
      // Error_Handler();
    }
}
/*****************************************************************************************************/
/*****************************************************************************************************/
void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/*****************************************************************************************************/
/*****************************************************************************************************/
void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress      = 0x20000000;
  MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable     = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number           = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
/*****************************************************************************************************/
/*****************************************************************************************************/
void delay(uint32_t time)
{
	//while(time--); // bu kod satiri 8 cycle'da tamamlanmakta. MCU calisma hizi 216MHZ
		            // 216000000/8=27000000
  //delay(21000000) seklinde kullanilirsa 1 saniyeye cok yakin bir süre elde edilir	
	
	while (time > 0) {
        time--;
    }          //12 cycle'da tamamlanir 216000000/12=18000000
	//delay(18000000) 1 saniye sürer
}
/*****************************************************************************************************/
/*****************************************************************************************************/
void TIM6_Config(void) 
{
	uint16_t prescaler=10799;
	uint16_t period=21599;
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;  // TIM6 clock enable

    TIM6->PSC = prescaler;
    TIM6->ARR = period;

    TIM6->CR1 &= ~TIM_CR1_DIR;  // Counter used as upcounter
    TIM6->CR1 &= ~TIM_CR1_UDIS; // Update event enabled

    TIM6->CR1 |= TIM_CR1_CEN;   // Counter enabled
}
/*****************************************************************************************************/
/*****************************************************************************************************/
void DelayMilliseconds(uint32_t milliseconds) 
	{
		
    TIM6->CNT = 0; // Counter reset

    while (TIM6->CNT < milliseconds); // Wait until the counter reaches the specified value
}
/*****************************************************************************************************/
/*****************************************************************************************************/
void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
/*****************************************************************************************************/
/*****************************************************************************************************/
