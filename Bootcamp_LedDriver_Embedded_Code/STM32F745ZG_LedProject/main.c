/**
  ******************************************************************************
  * @file    main.c
  * @author  Mete Sepetcioglu
  * @Tool    Keil MDK-ARM Professional Version 5.29.0.0 
  * @brief   Main program body
  ******************************************************************************/

#include "stm32f7xx.h"                  // Device header
#include "stm32f7xx_hal.h"
#include "led_driver.h"


void myDelay(uint32_t milliseconds) 
{
    uint32_t i, j;

    for (i = 0; i < milliseconds; i++) 
	  {
        for (j = 0; j < 18000; j++); 
    }
}


/*
HCLK = 216 MHz olmasi icin
Input Frequency 25MHz
HSE Enable
PLLM = /25
N = X432
P = /2
PLLCLK Select
*/

void my_RCC_Config()
{
	//Clock Frekansini ayalarmaka icin Hal kütüphanesi yerine register kodlama kullanildi.
	
	RCC->CR &=0x000083; // Reset Clock Line
	RCC->CR &= ~(1<<0); //HSI Disable
	RCC->CR |= 1 << 16; //HSEON
	//RCC->CR |= RCC_CR_HSEON;
	
  while (!(RCC->CR & (1<<17)));	// HSE clock ready flag, bayrak 1 olursa donguden cikar, Wait HSE Active
	RCC->CR |= 1 << 19; //CSSON: Clock security system enable
	
	
	//PLLM[5:0] = 11001 PLLM=25
	RCC->PLLCFGR |= 1<<0;    //PLLM[0] = 1
	RCC->PLLCFGR &= ~(1<<1); //PLLM[1] = 0
	RCC->PLLCFGR &= ~(1<<2); //PLLM[2] = 0
	RCC->PLLCFGR |= 1<<3;    //PLLM[3] = 1
	RCC->PLLCFGR |= 1<<4;    //PLLM[4] = 1
	
	//PLLN[14:6] = 432 yazilmali. 9 bit buyuklugunde 110110000
	RCC->PLLCFGR |= 432 <<6; //PLLN =432  !!!!!!!!!!!!! 1'ler yazildi ama 0'lar yazildi mi?
	/*RCC->PLLCFGR &= ~(1<<6);
	  RCC->PLLCFGR &= ~(1<<7);  6,7,8,9. bitler 0 yapmak istendiginde &= ~(960<<6); yazilabilir
	  RCC->PLLCFGR &= ~(1<<8);
	  RCC->PLLCFGR &= ~(1<<9);
	*/
	RCC->PLLCFGR &= ~(960<<6);
	RCC->PLLCFGR &= ~(1<<12);
	// PLLN[14:6] = 110110000 bitleri yazildi
	 
	
	//PLLP=2
	RCC->PLLCFGR  &= ~(1<<16);
	RCC->PLLCFGR &= ~(1<<17);
	
	//PLLSR Bit 22 
	//0: HSI clock selected as PLL and PLLI2S clock entry
  //1: HSE oscillator clock selected as PLL and PLLI2S clock entry
	RCC->PLLCFGR |= 1<<22; //PLL Source HSE
	
	
	//PLLQ =2  [27,26,25,24] = 0010
	RCC->PLLCFGR |= 1<<25; //25. bite 1 yazildi
	RCC->PLLCFGR  &= ~(1<<24);
	RCC->PLLCFGR  &= ~(1<<26);
	RCC->PLLCFGR  &= ~(1<<27);
	
	//CR Register, Bit 24 PLLON 0: PLL OFF, 1: PLL ON
	RCC->CR |= 1 << 24;
	while (!(RCC->CR & (1<<25)));	// Wait PLL Active
	
	//10: PLL selected as system clock
	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);
	
	while(! (RCC->CFGR & (1<<1) & ~(1<<0) )); //System Clok Select to PLL Clock Flag
  						
}

int main(void)
{
	my_RCC_Config();
	user_led_init();

  while(1)
  {
		user_led_toggle(Led_1);
		myDelay(50);
		user_led_toggle(Led_2);
		myDelay(50);
		user_led_toggle(Led_3);
		myDelay(50);
		user_led_toggle(Led_4);
		myDelay(50);
	
	}		
		
}


