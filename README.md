# Açıklama
Bu projede STM32F745ZGT6 işlemcisine özel fonksiyonlar ve uygulamalar geliştirilmektedir. Geliştirilen PCB üzerindeki sensör, entegre, haberleşme protokolleri ve çeşitli çevre birimleri kullanılmaktadır.<br/> <br/>
**Kullanılan Program** <br/> -Keil MDK-ARM Professional Version 5.29.0.0 <br/>
## [v.0.0.0.4] - 18.02.2024 Bootcamp_OptocuplerRead_Embedded_Code Klasörü Source Klasörü İçine Eklendi** <br/>
## [v.0.0.0.3] - 14.02.2024 Bootcamp_ADCDriver_Embedded_Code Klasörü Source Klasörü İçine Eklendi** <br/>
## [v.0.0.0.2] - 12.02.2024 Bootcamp_IDSwitchReader_Embedded_Code Klasörü Source Klasörü İçine Eklendi** <br/>
-Bootcamp_IDSwitchReader_Embedded_Code projesinde  üzerindeki işlemcinin pinlerine bağlı ID Switch entegresinden Interrupt yöntemiyle okuma yapmaktadır.  <br/>
**Yazılan Fonksiyonlar** <br/>
-ID_Switch_Init(); <br/>
-ID_Switch_DeInit(); <br/>
-SystemClock_Config_Fonc(); <br/>
-delay(); <br/>

## [v.0.0.0.1] -  Bootcamp_LedDriver_Project Klasörü Source Klasörü İçine Eklendi** <br/>
-Bootcamp_LedDriver_Project projesinde PCB üzerindeki işlemcinin pinlerine bağlı 4 adet ledi kontrol edebilmektir.  <br/>
**Yazılan Fonksiyonlar** <br/>
-myDelay(); <br/>
-my_RCC_Config(); <br/>
-user_led_init(); <br/>
-user_led_deinit(); <br/>
-user_led_on(); <br/>
-user_led_off(); <br/>
-user_led_toggle(); <br/>
