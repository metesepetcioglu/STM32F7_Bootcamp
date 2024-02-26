#include "button_relay_driver.h"

volatile uint8_t button_flag = 0;

void PinInit(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE(); //GPIO B ENABLE
	__HAL_RCC_GPIOE_CLK_ENABLE(); //GPIO E ENABLE
	
  // GPIO konfigürasyonu
	//B1 - User Buton - Exti Line 1
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; // Yükselen ve düsen kenar tetikleme
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // NVIC konfigürasyonu
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);	
	
	
	
	// GPIOE portu için konfigürasyon yapisi - Role kontrol pini
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Çikis (Push-Pull) modunda
	GPIO_InitStruct.Pin = GPIO_PIN_12 ; // 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; //GPIO hizi ayarlandi
	GPIO_InitStruct.Pull = GPIO_PULLDOWN; //Pull-down direnci secildi
	
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); //GPIOF portu bu konfigürasyon ile baslatilir
}

// Buton interrupt callback fonksiyonu

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  

    // Buton basildiginda flag'i set et
    button_flag = 1;
}


void EXTI1_IRQHandler(void)
{
    // Interrupt handler for EXTI1 (GPIO_PIN_1) external interrupt.

    // Delegates the handling of the interrupt to the HAL library,
    // providing the GPIO pin associated with EXTI1 (GPIO_PIN_1).
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
