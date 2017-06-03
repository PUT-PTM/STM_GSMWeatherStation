#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

#include "defines.h"
#include "tm_stm32f4_delay.h"

#include "gsm_usart.h"
#include "gsm.h"

extern int DHT11_temperature;
extern int DHT11_humidity;
extern int BMP180_pressure;

extern int tempReceived;
extern int pressReceived;
extern int humiReceived;

void GSM_run_config()
{
	GSM_send_string("AT\r\n");
	Delayms(1000);

	GSM_send_string("AT+CMGF=1\r\n");
	Delayms(1000);

	GSM_send_string("AT+CSCA=\"+48790998250\"\r\n");
	Delayms(1000);

	GSM_send_string("AT+CMGS=\"+48783419284\"\r\n");
	Delayms(1000);
}

void GSM_send_sms()
{
	char buffer[54];	
	sprintf(buffer, "Inside: T: %d P: %d H: %d\nOutside: T: %d P: %d H: %d", DHT11_temperature, BMP180_pressure, DHT11_humidity, tempReceived, pressReceived, humiReceived);
	GSM_send_string(buffer);
	Delayms(1000);
	GSM_send_char(26);
}
