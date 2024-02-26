/* The library currently contains the necessary functions for this project. 
   Additional functions will be added to the library in future projects as needed.
*/

#include "stm32f7xx_hal.h"
#include "MCU_Config.h"


/* Functions *****************************************************************/
void SystemClock_Config_Fonc(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

		  __HAL_RCC_PWR_CLK_ENABLE();
		  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


    // HSE Configuration
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // Initialization Error
        while (1);
    }

    // Select PLL as system clock source and configure the HCLK, PCLK1, PCLK2 clocks dividers
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        // Initialization Error
        while (1);
    }

}

/* Functions *****************************************************************/
void delay(uint32_t time)
{
    //while(time--); // This line of code completes in 8 cycles. MCU operating speed is 216MHz.
                    // 216000000/8=27000000
    // Using delay(21000000) in this form results in a duration very close to 1 second.

    while(time > 0)
        time--;          // Completes in 12 cycles. 216000000/12=18000000
    // Using delay(18000000) takes 1 second.
} //
