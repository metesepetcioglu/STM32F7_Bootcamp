#ifndef __INTERRUPT_DRIVER_H
#define __INTERRUPT_DRIVER_H

#include "stm32f7xx_hal.h"
#include <stdint.h>



// Interrupt tanimlari
#define EXTI_IRQn_B7 EXTI9_5_IRQn
#define EXTI_IRQn_B8 EXTI9_5_IRQn


#define BUTTON_PIN_B7 GPIO_PIN_7
#define BUTTON_PORT_B7 GPIOB
#define BUTTON_PIN_B8 GPIO_PIN_8
#define BUTTON_PORT_B8 GPIOB

#define LED_PIN_F4 GPIO_PIN_4
#define LED_PORT_F4 GPIOF
#define LED_PIN_F5 GPIO_PIN_5
#define LED_PORT_F5 GPIOF


#define D7_On   HAL_GPIO_WritePin(LED_PORT_F5, LED_PIN_F5, GPIO_PIN_SET)
#define D7_Off  HAL_GPIO_WritePin(LED_PORT_F5, LED_PIN_F5, GPIO_PIN_RESET)
#define D6_On   HAL_GPIO_WritePin(LED_PORT_F4, LED_PIN_F4, GPIO_PIN_SET)
#define D6_Off  HAL_GPIO_WritePin(LED_PORT_F4, LED_PIN_F4, GPIO_PIN_RESET)

void GPIOPinConfig(void);
void extiConfig(void);
void OptocuplerInit(void);
void OptocuplerDeInit(void);
void EXTI9_5_IRQHandler(void);
void Led_Controller(void);

#endif /*__INTERRUPT_DRIVER_H */
