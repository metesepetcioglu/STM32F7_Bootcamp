#ifndef __TEMPERATURE_READ_DRIVER_H
#define __TEMPERATURE_READ_DRIVER_H

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_adc.h"
#include "stm32f7xx_hal_dma.h"
#include <stdint.h>

extern volatile uint16_t adc_val;
/****************************************/
/*Interrupt-ADC Defines */

extern ADC_HandleTypeDef hadc1_int;
void IT_ADC1_Init(void);
void InputPin_config(void);
void TempADC_ITinit(void);
float TempADC_ITRead(void);
/****************************************/

/****************************************/
/*Poll For Conversion-ADC Defines */
extern ADC_HandleTypeDef hadc1_poll;

void POLL_ADC_Init(void);
void POLL_ADC_DeInit(void);
float TempADC_PollRead(void);
/****************************************/

/*DMA-ADC Defines */
extern ADC_HandleTypeDef hadc1_dma;
extern DMA_HandleTypeDef hdma_adc1; 

void DMA_ADC_Init(void);
void DMA_ADC_DeInit(void);
void Start_ADC_DMA(void);
void Stop_ADC_DMA(void);


extern uint32_t Adc_Buffer;
extern volatile float __adcdma__value;
float TempADC_DMARead(void);
/*****************************************/

#endif
