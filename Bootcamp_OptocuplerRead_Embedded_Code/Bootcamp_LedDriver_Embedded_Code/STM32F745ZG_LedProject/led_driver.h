#ifndef __LED_DRIVER_H
#define __LED_DRIVER_H

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include <stdint.h>

#define Led_1 GPIO_PIN_2
#define Led_2 GPIO_PIN_3
#define Led_3 GPIO_PIN_4
#define Led_4 GPIO_PIN_5


#define Led_1_GPIO_Port GPIOF
#define Led_2_GPIO_Port GPIOF
#define Led_3_GPIO_Port GPIOF
#define Led_4_GPIO_Port GPIOF



void user_led_init(void);
void user_led_deinit(void);
void user_led_on(uint8_t led_number);
void user_led_toggle(uint8_t led_number);
void user_led_off(uint8_t led_number);


#endif
