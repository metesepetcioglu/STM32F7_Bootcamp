/* HOW TO USE DRIVER */
/*
To use the library, simply call the OptocuplerInit() function.
After the function is called
- Optocoupler 1+ input will be connected to LED D10.
- Optocoupler 2+ input will be connected to LED D11.
You can watch the status of the LEDs by applying voltage values to the Optocoupler inputs.
*/


/* opto1+ girisine gerilim uygulanirsa b7 pini low okunacak, D10 Ledi yanacaktir.
      opto1+ girisine gerilim uygulanmadiginda b7 pini hihg okunacak, D10 Ledi sonecektir.
	    Bunun sebebi 74LVC2G14GW dijital tersleyici entegresinin kullanilmasidir.
	 */
   /* opto2+ girisine gerilim uygulanirsa b8 pini low okunacak, D11 Ledi yanacaktir.
      opto2+ girisine gerilim uygulanmadiginda b8 pini hihg okunacak, D11 Ledi sonecektir.
	    Bunun sebebi 74LVC2G14GW dijital tersleyici entegresinin kullanilmasidir.
	*/
	
	/*  When voltage is applied to opto1+ input, pin B7 will be read as low, and LED D10 will be lit.
      When no voltage is applied to opto1+ input, pin B7 will be read as high, and LED D10 will be turned off.
      This is due to the use of the 74LVC2G14GW digital inverter integrated circuit.
   */
   /* When voltage is applied to opto2+ input, pin B8 will be read as low, and LED D11 will be lit.
      When no voltage is applied to opto2+ input, pin B8 will be read as high, and LED D11 will be turned off.
      This is due to the use of the 74LVC2G14GW digital inverter integrated circuit.
   */
	 
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_exti.h"
#include "interrupt_driver.h"
 
 
// uint8_t b8Status=1;
// uint8_t b7Status=1;
// 
// Function to initialize the Interrupt and GPIO pins
void OptocuplerInit(void)
{
	GPIOPinConfig();
	extiConfig();
}
// Function to deinitialize the Optocoupler and GPIO pins
void OptocuplerDeInit(void)
{
    // Reset the settings of GPIO pins related to the Optocoupler
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7 | GPIO_PIN_8);

    // Disable the EXTI9_5_IRQn interrupt
    HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);

    // Reset the GPIOF pins
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

    // Deinitialize GPIOF pins
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_4 | GPIO_PIN_5);
    
}

// Interrupt handler for EXTI9_5_IRQn interrupt line
void EXTI9_5_IRQHandler(void)
{
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);   
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    	
}


// Callback function called on GPIO pin interrupt events

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   
        //HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	
        if (HAL_GPIO_ReadPin(BUTTON_PORT_B7, BUTTON_PIN_B7) == GPIO_PIN_SET)
        {
					  D6_Off;
           // b7Status = 1;
        }
				if (HAL_GPIO_ReadPin(BUTTON_PORT_B7, BUTTON_PIN_B7) == GPIO_PIN_RESET) 
				{
          //  b7Status = 0;
					  D6_On;
        }
				if (HAL_GPIO_ReadPin(BUTTON_PORT_B8, BUTTON_PIN_B8) == GPIO_PIN_SET) 
				{
					  D7_Off;
          //  b8Status = 1;
        }
				if (HAL_GPIO_ReadPin(BUTTON_PORT_B8, BUTTON_PIN_B8) == GPIO_PIN_RESET)
				{
					  D7_On;
          //  b8Status = 0;
        }
				
				//HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

 
 

void Led_Controller(void)
{
//	 
//        if (b7Status == 1 && b8Status == 1) 
//				{
//            // B7 ve B8 pinleri LOW durumdayken
//            
//            D6_Off;
//            D7_Off;
//        }
//				if (b7Status ==1 && b8Status == 0) 
//				{
//            // B7 LOW, B8 HIGH durumdayken
//            D6_Off;
//            D7_On;
//        }
//				if (b7Status == 0 && b8Status == 1) 
//				{
//            // B7 LOW, B8 HIGH durumdayken
//            D6_On;
//            D7_Off;
//        }
//				if (b7Status == 0 && b8Status == 0) 
//				{
//            // B7 LOW, B8 HIGH durumdayken
//					  D6_On;
//            D7_On;
//        }
}

// Function to configure GPIO pins
void GPIOPinConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	    // Enable clock signals for GPIO pin configurations
	__HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	__HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
	// Reset GPIOF pins
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  // Configure GPIOF pins (Led)
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  // Configure GPIOB pins (Opto)
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

} 


// Function to configure EXTI
void extiConfig(void)
{

  EXTI_HandleTypeDef h_exti;

  EXTI_ConfigTypeDef EXTI_InitStruct_PB7 = {0};
  EXTI_InitStruct_PB7.Line = EXTI_LINE_7;
  EXTI_InitStruct_PB7.Mode = EXTI_MODE_INTERRUPT;
  EXTI_InitStruct_PB7.Trigger = EXTI_TRIGGER_RISING;
  EXTI_InitStruct_PB7.GPIOSel = EXTI_GPIOB;
  HAL_EXTI_SetConfigLine(&h_exti, &EXTI_InitStruct_PB7);
	  /* EXTI interrupt init */


  EXTI_ConfigTypeDef EXTI_InitStruct_PB8 = {0};
  EXTI_InitStruct_PB8.Line = EXTI_LINE_8;
  EXTI_InitStruct_PB8.Mode = EXTI_MODE_INTERRUPT;
  EXTI_InitStruct_PB8.Trigger = EXTI_TRIGGER_RISING;
  EXTI_InitStruct_PB8.GPIOSel = EXTI_GPIOB;
  HAL_EXTI_SetConfigLine(&h_exti, &EXTI_InitStruct_PB8);
	
	
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);  // Kullanilan bir diger interrupt hat numarasi
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	
}


