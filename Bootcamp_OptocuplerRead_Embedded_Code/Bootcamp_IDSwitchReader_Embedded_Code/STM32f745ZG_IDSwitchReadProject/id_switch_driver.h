#ifndef __ID_SWITCH_RIVER_H
#define __ID_SWITCH_RIVER_H

#include "stm32f7xx_hal.h"
#include <stdint.h>

#define ID1_PIN GPIO_PIN_1
#define ID1_PORT GPIOG

#define ID2_PIN GPIO_PIN_0
#define ID2_PORT GPIOG

#define ID3_PIN GPIO_PIN_15
#define ID3_PORT GPIOF

#define ID4_PIN GPIO_PIN_14
#define ID4_PORT GPIOF


// External declaration of the global variable for storing ID information.
extern volatile uint8_t IDNUMBER;

// Function prototypes for configuring GPIO interrupts.
void Intterrupt_gpioConfigfonc(void);
void extiConfigfonc(void);
void ID_Switch_Init(void);
void ID_Switch_DeInit(void);


// Function prototype for reading the ID switches and returning the result.
int ID_Switch_Read(void);

// External Interrupt Handler function prototypes.
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
