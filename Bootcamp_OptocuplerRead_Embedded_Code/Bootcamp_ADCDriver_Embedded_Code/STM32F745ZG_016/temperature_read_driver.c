#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_adc.h"
#include "stm32f7xx_hal_dma.h"
#include "temperature_read_driver.h"



/* 

BU DRIVER NASIL KULLANILIR

#POLL FOR CONVERSION ADC OKUMASI
1. Adim) POLL_ADC_Init(); 
2. Adim) float sicakliksensordegeri = TempADC_PollRead(); 
  
		
##INTERRUPT ADC OKUMASI
1. Adim ) TempADC_ITinit(); fonksiyonu kullanildiginda adc_val degeri hafizada deger almaya baslayacaktir. 
2. Adim ) float sicakliksensordegeri= TempADC_ITRead();

###DMA ADC OKUMA

 1. Adim ) 	DMA_ADC_Init(); fonksiyonu kullanildiginda Adc_Buffer degeri hafizada deger almaya baslayacaktir. 
 2. Adim ) DMA_ADC_Init(); fonksiyonunu cagirdiktan sonra sensorun urettigi sicaklik degeri __adcdma__value degiskeninde saklanacaktir.
*/

volatile uint16_t adc_val=0;
uint32_t Adc_Buffer=0;
uint32_t adc_dma_val=0;
volatile float __adcdma__value=0;
volatile uint8_t readOnce = 0;
//HandeType Definitions
ADC_HandleTypeDef hadc1_int;
ADC_HandleTypeDef hadc1_poll;
ADC_HandleTypeDef hadc1_dma;
DMA_HandleTypeDef hdma_adc1;

/*****************************************************************************/
/*****************************************************************************/
// Configure input pin for ADC Pin A0
void InputPin_config()
{
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure PA0 as analog input
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}
/*****************************************************************************/
/*****************************************************************************/
// Initialize ADC for interrupt-driven mode
void TempADC_ITinit(void)
{
	IT_ADC1_Init();
	/*******************************/
	InputPin_config();
	/*******************************/
	HAL_ADC_Start_IT(&hadc1_int);
}
/*****************************************************************************/
/*****************************************************************************/
// Deinitialize ADC for interrupt-driven mode
void TempADC_ITDeinit(void)
{
    HAL_ADC_Stop_IT(&hadc1_int);
    HAL_ADC_DeInit(&hadc1_int);

    // ADC NVIC kesme önceligini ve durumunu sifirla
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_ClearPendingIRQ(ADC_IRQn);
}
/*****************************************************************************/
/*****************************************************************************/
// Initialize ADC for interrupt-driven mode
void IT_ADC1_Init(void)
{
  __HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE(); 
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1_int.Instance = ADC1;
  hadc1_int.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1_int.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1_int.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1_int.Init.ContinuousConvMode = ENABLE;
  hadc1_int.Init.DiscontinuousConvMode = DISABLE;
  hadc1_int.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1_int.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1_int.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1_int.Init.NbrOfConversion = 1;
  hadc1_int.Init.DMAContinuousRequests = DISABLE;
  hadc1_int.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
   if (HAL_ADC_Init(&hadc1_int) != HAL_OK)
  {
   // Error_Handler();
		// Handle error if necessary
  }

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1_int, &sConfig) != HAL_OK)
  {
   // Error_Handler();
		// Handle error if necessary
  }
	    // Enable ADC interrupt
    HAL_NVIC_SetPriority(ADC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
	 
}
/*****************************************************************************/
/*****************************************************************************/
// ADC interrupt handler
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1_int);
	  adc_val= HAL_ADC_GetValue(&hadc1_int);

}

float TempADC_ITRead(void)
{
		float tempVal = (float)adc_val* (3.3 / 4096 ); // tempVal V cinsinden deger uretmekte
    tempVal = tempVal * 1000; //tempVal mV 
    tempVal = (tempVal - 500) / 10;
	  return tempVal;
	
}
/*****************************************************************************/
/*****************************************************************************/
// Initialize ADC for polled mode
void POLL_ADC_Init(void)
{ 
	InputPin_config();
	__HAL_RCC_ADC1_CLK_ENABLE();

  hadc1_poll.Instance = ADC1;
  hadc1_poll.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1_poll.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1_poll.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1_poll.Init.ContinuousConvMode = DISABLE; 
  hadc1_poll.Init.DiscontinuousConvMode = DISABLE;
  hadc1_poll.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1_poll.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1_poll.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1_poll.Init.NbrOfConversion = 1;
  hadc1_poll.Init.DMAContinuousRequests = DISABLE;
  hadc1_poll.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1_poll) != HAL_OK)
  {
    //Error_Handler();
		// Handle error if necessary
  }
  ADC_ChannelConfTypeDef sConfig = {0};

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1_poll, &sConfig) != HAL_OK)
  {
    //Error_Handler();
		// Handle error if necessary
  }
}
/*****************************************************************************/
/*****************************************************************************/
// Read ADC value in polled mode
float TempADC_PollRead(void)
{	 
uint16_t pollAdcVal;
HAL_ADC_Start(&hadc1_poll); // Start the adc 
HAL_ADC_PollForConversion(&hadc1_poll, 100); // poll for conversion 
pollAdcVal = HAL_ADC_GetValue(&hadc1_poll); // get the adc value 
HAL_ADC_Stop(&hadc1_poll); // stop adc 

float tempVal = (float)pollAdcVal* (3.3 / 4096 ); // tempVal V cinsinden deger uretmekte
tempVal = tempVal * 1000; //tempVal mV 
tempVal = (tempVal - 500) / 10;
return tempVal;
	//0 Derece 500mV, her 10mv'da 1 derece
}

/*****************************************************************************/
/*****************************************************************************/
// Deinitialize ADC for polled mode
 void POLL_ADC_DeInit(void)
{
	HAL_ADC_DeInit(&hadc1_poll);
}
/*****************************************************************************/
/*****************************************************************************/
// Initialize ADC for DMA mode
 void DMA_ADC_Init(void)
{
    InputPin_config();

	  __HAL_RCC_DMA2_CLK_ENABLE();
	  __HAL_RCC_ADC1_CLK_ENABLE();
  
	  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    ADC_ChannelConfTypeDef sConfig = {0};
    hadc1_dma.Instance = ADC1;
    hadc1_dma.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1_dma.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1_dma.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1_dma.Init.ContinuousConvMode = ENABLE;
    hadc1_dma.Init.DiscontinuousConvMode = DISABLE;
    hadc1_dma.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1_dma.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1_dma.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1_dma.Init.NbrOfConversion = 1;
    hadc1_dma.Init.DMAContinuousRequests = DISABLE;  // DMA'yi etkinlestir
    hadc1_dma.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1_dma) != HAL_OK)
    {
       //  while (1);
			// Handle error if necessary
    }

    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1_dma, &sConfig) != HAL_OK)
    {
      //  while (1);
			// Handle error if necessary
    }

    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      //  while (1);
			// Handle error if necessary
    }
		
		__HAL_LINKDMA(&hadc1_dma, DMA_Handle, hdma_adc1);


    // DMA transfer complete interrupt enable
    __HAL_DMA_ENABLE_IT(&hdma_adc1, DMA_IT_TC);

    // Enable ADC DMA request
    hadc1_dma.Instance->CR2 |= ADC_CR2_DMA;
		
		HAL_ADC_Start_DMA(&hadc1_dma, &Adc_Buffer, 1);
	
	
}
/*****************************************************************************/
/*****************************************************************************/
// ADC DMA transfer complete callbac
	

/*****************************************************************************/
/*****************************************************************************/
 //Deinitialize ADC for DMA mode
void DMA_ADC_DeInit(void)
{
    // ADC'yi durdur
    HAL_ADC_Stop_DMA(&hadc1_dma);
    HAL_ADC_Stop(&hadc1_dma);
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
	  HAL_ADC_DeInit(&hadc1_dma);
	  HAL_DMA_DeInit(&hdma_adc1);
}

void DMA2_Stream0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_adc1);
  adc_dma_val = Adc_Buffer;
	__adcdma__value = (float)adc_dma_val * (3.3 / 4096 ); // tempVal V cinsinden deger uretmekte
	__adcdma__value = __adcdma__value*1000;
	__adcdma__value = (__adcdma__value - 500) / 10;
}

float TempADC_DMARead(void)
{
  return __adcdma__value;
}
