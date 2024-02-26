//***********************************How to Use This Library***********************/
// To use the library, simply call the ID_Switch_Init() function.
// After calling ID_Switch_Init(), the IDNUMBER variable starts generating value.
// You can use IDNUMBER in the main program or assign it to another variable.
// By using the ID_Switch_DeInit function, you can disable interrupts and deinitialize GPIO pins.

/***********************Bu kutuphane nasil kullanilir****************************/
//Kütüphaneyi kullanmak icin 	ID_Switch_Init() fonksiyonunu cagirmak yeterlidir.
//ID_Switch_Init() fonksiyonunu cagirdiktan sonra IDNUMBER degiskeni deger üretmeye baslar.
//ana programda IDNUMBER'i kullanabilir ya da baska bir degiskene atayabilirsiniz.
//ID_Switch_DeInit fonksiyonunu kullanarak ise kesmeleri devre disi birakabilir ve GPIO pinlerini deinit edebilirsiniz.

#include "stm32f7xx_hal.h"
#include "id_switch_driver.h"

volatile uint8_t IDNUMBER=0;
	
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // This function is called when an EXTI interrupt is triggered, indicating a pin change.

    // Check the state of GPIOG, GPIO_PIN_1 (PG1) and update the corresponding bit in IDNUMBER.
    if (HAL_GPIO_ReadPin(ID1_PORT, ID1_PIN) == GPIO_PIN_SET) 
    {
        // If PG1 is in a high state, set the first bit of IDNUMBER to 1.
        IDNUMBER |= (1 << 0);
    }
    else 		
    {
        // If PG1 is in a low state (RESET), set the first bit of IDNUMBER to 0.
        IDNUMBER &= ~(1 << 0);
    }

    // Check the state of GPIOG, GPIO_PIN_0 (PG0) and update the corresponding bit in IDNUMBER.
    if (HAL_GPIO_ReadPin(ID2_PORT, ID2_PIN) == GPIO_PIN_SET) 
    {
        // If PG0 is in a high state, set the second bit of IDNUMBER to 1.
        IDNUMBER |= (1 << 1);
    }
    else 
    {
        // If PG0 is in a low state (RESET), set the second bit of IDNUMBER to 0.
        IDNUMBER &= ~(1 << 1);
    }

    // Check the state of GPIOF, GPIO_PIN_15 (PF15) and update the corresponding bit in IDNUMBER.
    if (HAL_GPIO_ReadPin(ID3_PORT, ID3_PIN) == GPIO_PIN_SET) 
    {
        // If PF15 is in a high state, set the third bit of IDNUMBER to 1.
        IDNUMBER |= (1 << 2);
    }
    else 
    {
        // If PF15 is in a low state (RESET), set the third bit of IDNUMBER to 0.
        IDNUMBER &= ~(1 << 2);
    }

    // Check the state of GPIOF, GPIO_PIN_14 (PF14) and update the corresponding bit in IDNUMBER.
    if (HAL_GPIO_ReadPin(ID4_PORT, ID4_PIN) == GPIO_PIN_SET) 
    {
        // If PF14 is in a high state, set the fourth bit of IDNUMBER to 1.
        IDNUMBER |= (1 << 3);
    }
    else 
    {
        // If PF14 is in a low state (RESET), set the fourth bit of IDNUMBER to 0.
        IDNUMBER &= ~(1 << 3);
    }
}

	
void extiConfigfonc()
{
    // This function configures the EXTI (External Interrupt) settings for specific GPIO pins.

    // Configure EXTI for GPIO_PIN_0 (external interrupt line 0)
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);    // Set the priority of EXTI0_IRQn to 0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);            // Enable EXTI0_IRQn

    // Configure EXTI for GPIO_PIN_1 (external interrupt line 1)
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);    // Set the priority of EXTI1_IRQn to 0
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);            // Enable EXTI1_IRQn

    // Configure EXTI for GPIO_PIN_14 and GPIO_PIN_15 (external interrupt lines 14 and 15)
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);    // Set the priority of EXTI15_10_IRQn to 0
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);            // Enable EXTI15_10_IRQn
}

void Intterrupt_gpioConfigfonc()
{
	// ID1-PG1, ID2-PG0, ID3-PF15, ID4-PF14
	GPIO_InitTypeDef myGPIOInitStructure;
	
  __HAL_RCC_GPIOG_CLK_ENABLE(); // Port G Enable	
	myGPIOInitStructure.Mode = GPIO_MODE_IT_RISING;
	myGPIOInitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	myGPIOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG, &myGPIOInitStructure);
	
	
  __HAL_RCC_GPIOF_CLK_ENABLE(); // Port F Enable	
	myGPIOInitStructure.Mode = GPIO_MODE_IT_RISING;
	myGPIOInitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_15;
	myGPIOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &myGPIOInitStructure);
	

}
void ID_Switch_Init(void)
{
	extiConfigfonc();
	Intterrupt_gpioConfigfonc();
}


void ID_Switch_DeInit(void)
{
    // Deinitialize ID switch configurations, e.g., disable external interrupts

    // Disable EXTI for GPIO_PIN_0 (external interrupt line 0)
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);

    // Disable EXTI for GPIO_PIN_1 (external interrupt line 1)
    HAL_NVIC_DisableIRQ(EXTI1_IRQn);

    // Disable EXTI for GPIO_PIN_14 and GPIO_PIN_15 (external interrupt lines 14 and 15)
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);

    // Deinitialize GPIOG and GPIOF
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0 | GPIO_PIN_1);
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_14 | GPIO_PIN_15);
}


void EXTI0_IRQHandler(void)
{
    // Interrupt handler for EXTI0 (GPIO_PIN_0) external interrupt.

    // Delegates the handling of the interrupt to the HAL library,
    // providing the GPIO pin associated with EXTI0 (GPIO_PIN_0).
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI1_IRQHandler(void)
{
    // Interrupt handler for EXTI1 (GPIO_PIN_1) external interrupt.

    // Delegates the handling of the interrupt to the HAL library,
    // providing the GPIO pin associated with EXTI1 (GPIO_PIN_1).
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void EXTI15_10_IRQHandler(void)
{
    // Interrupt handler for EXTI15_10 (GPIO_PIN_14 and GPIO_PIN_15) external interrupts.

    // Delegates the handling of the interrupt to the HAL library,
    // providing the GPIO pins associated with EXTI15_10 (GPIO_PIN_14 and GPIO_PIN_15).
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}


