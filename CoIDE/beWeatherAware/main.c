#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_i2c.h"
#include "misc.h"

#include "dht11.h"
#include "bmp180.h"
#include "usart.h"
#include "tim4.h"
#include "usart_functions.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_bmp180.h"

int counter = 0;

int main(void) 
{
	SystemInit();
	
	DHT11_run_config();
	USART_run_config();
	TIM4_run_config();
	GSM_USART_run_config();
	TM_DELAY_Init();
	BMP180_check_status();
	LCD_run_config();
	GSM_run_config();
	

	// 1. ogolnie w mainie sie nic nie dzieje
	// 2. podlaczamy wszystko i czekamy na sygnal z kompa zeby po prostu dostac OUTSIDE warunki
	// 3. co 5s zmienia sie wyswietlacz, raz INSIDE raz OUTSIDE
	// 4. w TIM4Handler jest zmienna counter i zrobilem ze raz na 30s wysyla sms, jak zmienimy if'a na inna wartosc niz 6, no to bedzie odpowiednio innaczej wysylal
	// 5. raz na 10s pobieram wyniki z naszych czunikow - oczywiscie ten czas tez mozna zmienic jak wyzej, jak bedziemy chcieli pokazac runtime wyniki, no to sie odkomentuje while(1) w mainie
	// 6. jak otrzymamy znak 's' to my wysylamy do kompa nasze warunki
	// 7. jak cokolwiek innego to my cos otrzymujemy
	
	while (1) 
	{		
		// DHT11_read_data();
		// BMP180_read_data();
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		counter++;
		LCD_display();
		
		if (counter == 2)
		{
			DHT11_read_data();
			BMP180_read_data();
		}
		else if (counter == 6)
		{
			GSM_send_sms();
			counter = 0;
		}
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void USART3_IRQHandler(void) 
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		uint8_t received = USART3->DR;
		
		if (received == 's')
		{
			USART_send_conditions();
		} 
		else
		{
			USART_read_conditions(received);			
		}
	}
}






