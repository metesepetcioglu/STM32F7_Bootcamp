#include "led_driver.h"

/*
##### Bu driver nasil kullanilir #####
==============================================================================
1- Ledlerle islem yapilmak isteniyorsa once user_led_init(); fonksiyonu cagirilmali
2- Ardindan user_led_on(Led_x) ,user_led_off(Led_x), user_led_toggle(Led_x) fonksiyonlari kullanilabilir hale gelir.
3- Led_x -->> x=1, x=2, x=3, x=4 gecerli ledlerdir. Diger girilen ledler gecersizdir.
4- user_led_on(Led_x); Bu fonksiyon Ledi acmak icin kullanilir.
5- user_led_off(Led_x); Bu fonksiyon Ledi kapatmak icin kullanilir.
6- user_led_toggle(Led_x); Bu fonksiyon Ledin son cikis durumunu terslemek icin kullanilir.

***********************************Ornek bir kullanim***************************************
********************************************************************************************		
	int main(void){	
	  user_led_init(); // LED driver'ini baslat  
    user_led_on(Led_1); // Led 1'i ac    
    HAL_Delay(1000); // 1 saniye bekle   
    user_led_on(Led_2); // Led 2'yi ac    
    HAL_Delay(1000); // 1 saniye bekle
    user_led_off(Led_3); // Led 3'u kapat    
    HAL_Delay(1000); // 1 saniye bekle    
    user_led_toggle(Led_4); // Led 4'u toggle (durumunu degistir)    
    HAL_Delay(1000); // 1 saniye bekle    
    user_led_deinit(); // LED driver'ini sifirla (de-init) }		
********************************************************************************************		
********************************************************************************************		
*/


void user_led_init(void)
{
		GPIO_InitTypeDef myGPIOInitStructure;
	
	__HAL_RCC_GPIOF_CLK_ENABLE(); //GPIO F ENABLE
	
	// GPIOF portu için konfigürasyon yapisi (myGPIOInitStructure) hazirlanir
	myGPIOInitStructure.Mode = GPIO_MODE_OUTPUT_PP; // Çikis (Push-Pull) modunda
	myGPIOInitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5; // PF2, PF3, PF4, PF5 pinleri seçilir
	myGPIOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH; //GPIO hizi ayarlandi
	myGPIOInitStructure.Pull = GPIO_PULLDOWN; //Pull-down direnci secildi
	
	HAL_GPIO_Init(GPIOF, &myGPIOInitStructure); //GPIOF portu bu konfigürasyon ile baslatilir
}

void user_led_deinit(void)
{
    GPIO_InitTypeDef myGPIOInitStructure;

// GPIOF portundaki belirli pinlerin konfigürasyonu sifirlanir (de-init)
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
   
    //__HAL_RCC_GPIOF_CLK_DISABLE(); GPIOF clock kapatilacaksa kullanilabilir.
	  // Ancak GPIOF clock hattini kapatmak riskli. 
	  // Sadece HAL_GPIO_DeInit fonksiyonuyla gecerli pinler varsayilana donduruldu
}

void user_led_on(uint8_t led_number)
{
	//Bu fonksiyonu kullanmak icin once user_led_init(); cagirilmali
	/*
	 user_led_on fonksiyonunda cagir
	*/
	
 	if (led_number == Led_1 || led_number == Led_2 || led_number == Led_3 || led_number == Led_4) 
		{
        HAL_GPIO_WritePin(GPIOF, led_number, GPIO_PIN_SET); //Gerecli Pini(Ledi) Acar.
    } 
	else
		{
			/*   If blogu sadece ledlerin pinlerine bakar. 
			     diger pinler girilirse HAL_GPIO_WritePin fonksiyonuna girmeyeceginden 
			     karisiklik ve yanlislik olmamasinin onune gecildi.
           else girdiginde hic bir sey yapmadan fonksiyondan cikar.               */
    }
	
}

void user_led_off(uint8_t led_number) 
{
    if (led_number == Led_1 || led_number == Led_2 || led_number == Led_3 || led_number == Led_4) 
		{
        HAL_GPIO_WritePin(GPIOF, led_number, GPIO_PIN_RESET); //Gecerli Pini(Ledi) Kapatir
    } 
	else
		{
			/*   If blogu sadece ledlerin pinlerine bakar. 
			     diger pinler girilirse HAL_GPIO_WritePin fonksiyonuna girmeyeceginden 
			     karisiklik ve yanlislik olmamasinin onune gecildi.
           else girdiginde hic bir sey yapmadan fonksiyondan cikar.               */
    }

}

void user_led_toggle(uint8_t led_number) 
{
    if (led_number == Led_1 || led_number == Led_2 || led_number == Led_3 || led_number == Led_4) 
		{
        HAL_GPIO_TogglePin(GPIOF, led_number); //Gecerli Pinin cikis durumunu tersler
    } 
	else
		{
			/*   If blogu sadece ledlerin pinlerine bakar. 
			     diger pinler girilirse HAL_GPIO_TogglePin fonksiyonuna girmeyeceginden 
			     karisiklik ve yanlislik olmamasinin onune gecildi.
           else girdiginde hic bir sey yapmadan fonksiyondan cikar.               */
    }

}


