#ifndef __SEVENSEGMENTDISPLAY_DRIVER_H
#define __SEVENSEGMENTDISPLAY_DRIVER_H

#include "stm32f7xx_hal.h"
#include <stdint.h>


#define D0_Pin GPIO_PIN_14
#define D1_Pin GPIO_PIN_11
#define D2_Pin GPIO_PIN_10
#define D3_Pin GPIO_PIN_13
#define D_Port GPIOE

#define BL1_Pin GPIO_PIN_15
#define LE1_Pin GPIO_PIN_14
#define DP1_Pin GPIO_PIN_15
#define BL1_Port GPIOE
#define LE1_Port GPIOD
#define DP1_Port GPIOD

#define BL2_Pin GPIO_PIN_0
#define LE2_Pin GPIO_PIN_2
#define DP2_Pin GPIO_PIN_2
#define BL2_Port GPIOC
#define LE2_Port GPIOC
#define DP2_Port GPIOG



#define Led1_On HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2,GPIO_PIN_SET)
#define Led2_On HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3,GPIO_PIN_SET)
#define Led3_On HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4,GPIO_PIN_SET)
#define Led4_On HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5,GPIO_PIN_SET)

#define Led1_Off HAL_GPIO_WritePin(GPIOF, GPIO_PIN_2,GPIO_PIN_RESET)
#define Led2_Off HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3,GPIO_PIN_RESET)
#define Led3_Off HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4,GPIO_PIN_RESET)
#define Led4_Off HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5,GPIO_PIN_RESET)



void DSConfig(void);

void DS1(uint8_t value);
void DS2(uint8_t value);
	
void DS1_DOT(void);
void DS2_DOT(void);
void DS1_Clear(void);

void twoDigitNumber(uint8_t val);
void terstentwoDigitNumber(uint8_t val);
void InitLEDs(void);

#endif /*__SEVENSEGMENTDISPLAY_DRIVER_H */

