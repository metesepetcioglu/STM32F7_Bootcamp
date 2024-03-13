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
	
	
		// 0-9 araligina çekmek
	//...
	// 0000 0001
	
//	uint8_t D1_sts = (value | 0x01) == 0x01; //true ya da false return edecek
//	uint8_t D2_sts = (value | 0x02) == 0x02;
//	uint8_t D3_sts = (value | 0x04) == 0x04; 
//	uint8_t D4_sts = (value | 0x08) == 0x08;
uint8_t D1_sts = (value & 0x01) != 0;
uint8_t D2_sts = (value & 0x02) != 0;
uint8_t D3_sts = (value & 0x04) != 0;
uint8_t D4_sts = (value & 0x08) != 0;
	
	//9 -> 1001  - 0,3 Set
	//8 -> 1000  - 3 Set
	//7 -> 0111  - 0,1,2 Set
	//6 -> 0110  - 1,2 Set
	//5 -> 0101  - 0,2 Set
	//4 -> 0100  
	//3 -> 0011  
	//2 -> 0010
	//1 -> 0001
	//0 -> 0000
	
	HAL_GPIO_WritePin(D_Port, D0_Pin | D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
	
	if(D1_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin, GPIO_PIN_SET);
		//Led1_On; 
	}
	if(D2_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin, GPIO_PIN_SET);
		//Led2_On;
	}
	if(D3_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D2_Pin, GPIO_PIN_SET);
		//Led3_On;
	}
	if(D4_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_SET);
		//Led4_On;
	}
	
}

// Display a digit (0-9) on the second 7-segment display (DS2)
void DS2(uint8_t value)
{
		HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DP2_Port,DP2_Pin, GPIO_PIN_RESET);

uint8_t D1_sts = (value & 0x01) != 0;
uint8_t D2_sts = (value & 0x02) != 0;
uint8_t D3_sts = (value & 0x04) != 0;
uint8_t D4_sts = (value & 0x08) != 0;

	
	HAL_GPIO_WritePin(D_Port, D0_Pin | D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_RESET);
	if(D1_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D0_Pin, GPIO_PIN_SET);
		//Led1_On; 
	}
	if(D2_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D1_Pin, GPIO_PIN_SET);
		//Led2_On;
	}
	if(D3_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D2_Pin, GPIO_PIN_SET);
		//Led3_On;
	}
	if(D4_sts == 1)
	{
		HAL_GPIO_WritePin(D_Port,D3_Pin, GPIO_PIN_SET);
		//Led4_On;
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
//	 while(count)
//	 {
//   DS1(onlarbasamagi);	
//   //HAL_Delay(1);
//   //delay(1800); //1 ns
//		 delay(1200);
//   //delay(900000);
//   DS2(birlerbasamagi);
//	 //delay(1800); //1 ns
//		 delay(600);
//	 count--;
//	 }
   DS2(birlerbasamagi);
   HAL_Delay(5);	 
	 DS1(onlarbasamagi);	 
	 HAL_Delay(5);
 }		  	
 else
 {
	HAL_GPIO_WritePin(BL2_Port,BL2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BL1_Port,BL1_Pin, GPIO_PIN_RESET);
 }
}



void terstentwoDigitNumber(uint8_t val)
{
	if(val >= 0 && val <= 99)
 {	
	uint8_t birlerbasamagi, onlarbasamagi;
	 
	birlerbasamagi = val % 10;
	onlarbasamagi = val/10;
	 
	 DS1(onlarbasamagi);
   DS2(birlerbasamagi); 
	 
 }		  	

}



// Initialize F4,F5 pin LEDs 
void InitLEDs(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOF_CLK_ENABLE();


  GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct); 
}