#include "stm32f7xx_hal.h"
#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "cmsis_os.h"
#include "SevenSegmentDisplay_Driver.h"
#include "button_relay_driver.h"


// Iki periodic ve bir oneshot thread i�in tanimlamalar
osThreadId_t thread_id_periodic_ds1, thread_id_oneshot;

// Thread callback fonksiyonlari
void Thread_Periodic_DS1(void *argument);

void Thread_OneShot(void *argument);

// Sayac degiskenleri
uint8_t counter_period = 0;
//uint8_t counter_period_2 = 0;

// Periodik thread �zellikleri
const osThreadAttr_t thread_attr_periodic_ds1 = {
  .name = "PeriodicThreadDS1",
  .priority = osPriorityNormal,
  .stack_size = 128
};


// OneShot thread �zellikleri
const osThreadAttr_t thread_attr_oneshot = {
  .name = "OneShotThread",
  .priority = osPriorityNormal,
  .stack_size = 128
};


// Thread baslatma fonksiyonu
void StartThreads(void)
{
  // Periodik thread DS1 i�in olustur
  thread_id_periodic_ds1 = osThreadNew(Thread_Periodic_DS1, NULL, &thread_attr_periodic_ds1);


  // OneShot thread olustur
  thread_id_oneshot = osThreadNew(Thread_OneShot, NULL, &thread_attr_oneshot);
}

// Periodik thread DS1 callback fonksiyonu
void Thread_Periodic_DS1(void *argument)
{
  while (1) 
	{
	 //0-99 arasi sayac
		twoDigitNumber(counter_period);
				
    counter_period++;
    if (counter_period > 99) 
		{
      counter_period = 0;
    }

    osDelay(1000); // 1 saniye bekle
  }
}



// OneShot thread callback fonksiyonu
void Thread_OneShot(void *argument)
{
  while (1) 
  {
      //user butona basildiginda role girisini aktif eder ve Led4 (PF5) yakar
      // 10 saniye bekledikten sonra role anahtarlamasini kapatir ve Led4 soner.
    if (button_flag == 1) 
		{
					
      // Flag'i sifirla
      button_flag = 0;

			// Butona basildiginda Role Ac (E12 pini HIGH yap)
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_SET); //kullanici ledi'ni yak
      // E12 pini LOW yap
			osDelay(10000);
      HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET); //role kapat
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET); //kullanici ledi'ni kapat

    }

    osDelay(100); // 100 ms bekle
  }
}
