/*
DPY DP 1 - PD15
DPY DP 2 - PG2

DPY BL 1 - PE15
DPY LE 1 - PD14

DPY BL 2 - PC0
DPY LE 2 - PC2
	
DPY D0 - PE14
DPY D1 - PE11
DPY D2 - PE10
DPY D3 - PE13

***gerekli bilgiler Resource klasörünün içindeki cd74hc4511.pdf dosyasininin 10. sayfadaki tablodan alindi ***
***The necessary information was taken from the table on page 10 of the cd74hc4511.pdf file in the Resource folder*** 

BL - LOW ise tum cikislar LOW
LT - LOW ise tum cikislar HIGH
--7Segment Displayi kullanabilmek icin CD74HC4511M96 entegresinin girisleri LE-LOW, BL-HIGH, LT-HIGH olmali--
--To use 7 Segment Display The inputs of the CD74HC4511M96 integrated should be LE-LOW, BL-HIGH, LT-HIGH--

negatif (-) karakteri yapmak icin 7 Segmentin G girisini High diger girisleri low yapmak gerekiyor.
Ancak kullanilan cd74hc4511m96 entegresi bu dijital cikisi vermiyor.
*/ 
#include "SevenSegmentDisplay_Driver.h"
#include "MCU_Config.h"


// This function configures GPIO pins for the 7-segment display.
	// It initializes the necessary GPIO pins for segments (D0-D3),
void DSConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	    // Enable clock signals for GPIO pin configurations
	__HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	
	__HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
	// Reset GPIO pins 
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0  | GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13 |GPIO_PIN_14 |GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);

  // Configure GPIOC pins - PC0 - PC2
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
  // Configure GPIOD pins - PD14 - PD15
	GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
  // Configure GPIOE pins - PE10 - PE11 - PE13 - PE14 - PE15
	GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13 |GPIO_PIN_14 |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	// Configure GPIOG pin - PG2
	GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	//For the 7 segment display to work, the LE connections must always be LOW.
	HAL_GPIO_WritePin(LE1_Port,LE1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LE2_Port,LE2_Pin, GPIO_PIN_RESET);
}


// Display a digit (0-9) on the first 7-segment display (DS1)
void DS1(uint8_t value)
{
		HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DP1_Port,DP1_Pin, GPIO_PIN_RESET);
	
	if(value == 0)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
	}
	else if(value == 1)
	{
		HAL_GPIO_WritePin(D_Port, D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin , GPIO_PIN_SET);
	}
	else if(value == 2)
	{
		HAL_GPIO_WritePin(D_Port, D0_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D1_Pin , GPIO_PIN_SET);
	}
	else if(value == 3)
	{
		HAL_GPIO_WritePin(D_Port,D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin , GPIO_PIN_SET);
	}
	else if(value == 4)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 5)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 6)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D1_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 7)
	{
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 8)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_SET);
	}
	else if(value == 9)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin | D2_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D3_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
	}
	//HAL_Delay(5);
}

// Display a digit (0-9) on the second 7-segment display (DS2)
void DS2(uint8_t value)
{
		HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DP2_Port,DP2_Pin, GPIO_PIN_RESET);
		
	if(value == 0)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
	}
	else if(value == 1)
	{
		HAL_GPIO_WritePin(D_Port, D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin , GPIO_PIN_SET);
	}
	else if(value == 2)
	{
		HAL_GPIO_WritePin(D_Port, D0_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D1_Pin , GPIO_PIN_SET);
	}
	else if(value == 3)
	{
		HAL_GPIO_WritePin(D_Port,D2_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin , GPIO_PIN_SET);
	}
	else if(value == 4)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 5)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 6)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D1_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 7)
	{
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin , GPIO_PIN_SET);
	}
	else if(value == 8)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin | D1_Pin | D2_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_SET);
	}
	else if(value == 9)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin | D2_Pin , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D_Port,D0_Pin | D3_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
	}
}

// Display a dot on the first 7-segment display (DS1)
void DS1_DOT(void)
	{
		HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
		
//		HAL_GPIO_WritePin(D_Port,D1_Pin | D3_Pin , GPIO_PIN_SET);
//		HAL_GPIO_WritePin(D_Port,D0_Pin | D2_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(DP1_Port,DP1_Pin, GPIO_PIN_SET);

	}
	
// Clear the first 7-segment display (DS1)
void DS1_Clear(void)
{
	HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DP1_Port,DP1_Pin, GPIO_PIN_RESET);
}

// Clear the second 7-segment display (DS2)
void DS2_Clear(void)
{
	HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DP2_Port,DP2_Pin, GPIO_PIN_RESET);
}

// Display a dot on the second 7-segment display (DS2)
// I could not use this function successfully
void DS2_DOT(void)
	{
		HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
//		
//		HAL_GPIO_WritePin(D_Port,D1_Pin | D3_Pin , GPIO_PIN_SET);
//		HAL_GPIO_WritePin(D_Port,D0_Pin | D2_Pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(DP2_Port,DP2_Pin, GPIO_PIN_SET);
//		HAL_Delay(1);
	}


// Display a two-digit number on both 7-segment displays (DS1 and DS2)
void twoDigitNumber(uint8_t val)
{
	if(val >= 0 && val <= 99)
 {	
	uint8_t birlerbasamagi, onlarbasamagi;
	 
	birlerbasamagi = val % 10;
	onlarbasamagi = val/10;
	 
	 uint64_t count=10000;
	 while(count)
	 {
   DS1(onlarbasamagi);	
   //HAL_Delay(1);
   //delay(1800); //1 ns
		 delay(1200);
   //delay(900000);
   DS2(birlerbasamagi);
	 //delay(1800); //1 ns
		 delay(600);
	 count--;
	 }

 }		 

 	
 else
 {
	HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
 }
}


// Initialize F4,F5 pin LEDs 
void InitLEDs(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOF_CLK_ENABLE();

  // F4 pin
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  // F5 pin
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}