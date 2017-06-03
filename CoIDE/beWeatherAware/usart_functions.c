#include "stm32f4xx_gpio.h"

#include "usart_functions.h"
#include "usart.h"

extern int DHT11_temperature;
extern int DHT11_humidity;
extern int BMP180_pressure;

double	d1 = 0, d2 = 0, d3 = 0;
int		i1 = 0, i2 = 0, i3 = 0, i4 = 0;

int temp_preview = 0, press_preview = 0, humi_preview = 0;

int byteNumber = 0;

int tempReceived_1  = 0, tempReceived_2  = 0, tempReceived    = 0;
int pressReceived_1 = 0, pressReceived_2 = 0, pressReceived_3 = 0, pressReceived_4 = 0, pressReceived = 0;
int humiReceived_1  = 0, humiReceived_2  = 0, humiReceived    = 0;

void USART_read_conditions(uint8_t received)
{
	switch (++byteNumber)
	{
		case 1:
			tempReceived_1 = getNumber(received);
			break;
		case 2:
			tempReceived_2 = getNumber(received);
			tempReceived = tempReceived_1 * 10 + tempReceived_2; /******************************************************/
			break;
		case 3:
			pressReceived_1 = getNumber(received);
			break;
		case 4:
			pressReceived_2 = getNumber(received);
			break;
		case 5:
			pressReceived_3 = getNumber(received);
			break;
		case 6:
			pressReceived_4 = getNumber(received);
			pressReceived = pressReceived_1 * 1000 + pressReceived_2 * 100 + pressReceived_3 * 10 + pressReceived_4; /******************************************************/
			break;
		case 7:
			humiReceived_1 = getNumber(received);
			break;
		case 8:
			humiReceived_2 = getNumber(received);
			humiReceived = humiReceived_1 * 10 + humiReceived_2; /******************************************************/
			byteNumber = 0;
			break;
		default:
			byteNumber = 0;
			break;		
	}
}

void USART_send_conditions()
{
	sendTemperature();
	sendPressure();
	sendHumidity();
}

void sendTemperature()
{
	// zakres 0 - 50 °C
	if (DHT11_temperature >= 10)
	{
		// przyklad dla 39
		d1 = ((double) DHT11_temperature) / (10);	// 3.9
		i1 = ((int) d1);							// 3 -> wysylamy
		i2 = (d1 - i1) * 10;						// 0.9 * 10 = 9 -> wysylamy
		
		USART_send_char(i1 + 48);
		USART_send_char(i2 + 48);
		
		temp_preview = i1 * 10 + i2; /******************************************************/
	}
	else 
	{
		// przyklad dla 8
		i1 = 0;					// 0 -> wysylamy
		i2 = DHT11_temperature;	// 8 -> wysylamy
		
		USART_send_char(i1 + 48);
		USART_send_char(i2 + 48);
		
		temp_preview = i1 * 10 + i2; /******************************************************/
	}
}

void sendHumidity()
{
	// zakres 20 - 90 %RH
	// przyklad dla 68
	d1 = ((double) DHT11_humidity) / (10);	// 6.8
	i1 = ((int) d1);						// 6 -> wysylamy
	i2 = (d1 - i1) * 10;					// 0.8 * 10 = 8 -> wysylamy
	
	USART_send_char(i1 + 48);
	USART_send_char(i2 + 48);

	humi_preview = i1 * 10 + i2; /******************************************************/
}

void sendPressure() 
{
	// zakres 300 - 1100 hPa
	if (BMP180_pressure >= 1000)
	{
		// przyklad dla 1005
		d1 = ((double) BMP180_pressure) / (1000); 	// 1.005
		i1 = ((int) d1);							// 1 -> wysylamy
		d2 = (d1 - i1) * 10;						// 0.005 * 10 = 0.05
		i2 = ((int) d2);							// 0 -> wysylamy
		d3 = (d2 - i2) * 10;						// 0.05 * 10 = 0.5
		i3 = ((int) d3);							// 0 -> wysylamy 
		i4 = (d3 - i3) * 10;						// 0.5 * 10 = 5 -> wysylamy
		
		USART_send_char(i1 + 48);
		USART_send_char(i2 + 48);
		USART_send_char(i3 + 48);
		USART_send_char(i4 + 48);
		
		press_preview = i1 * 1000 + i2 * 100 + i3 * 10 + i4; /******************************************************/
	}
	else
	{
		// przyklad dla 997
		i1 = 0;										// 0 -> wysylamy
		d1 = ((double) BMP180_pressure) / (100); 	// 9.97
		i2 = ((int) d1);							// 9 -> wysylamy
		d2 = (d1 - i2) * 10;						// 0.97 * 10 = 9.7
		i3 = ((int) d2);							// 9 -> wysylamy
		i4 = (d2 - i3) * 10;						// 9.7 * 10 = 7 -> wysylamy
		
		USART_send_char(i1 + 48);
		USART_send_char(i2 + 48);
		USART_send_char(i3 + 48);
		USART_send_char(i4 + 48);
		
		press_preview = i1 * 1000 + i2 * 100 + i3 * 10 + i4; /******************************************************/
	}
}

int getNumber(uint8_t received) 
{
	switch (received)
	{
		case '0':	return 0;
		case '1':	return 1;
		case '2':	return 2;
		case '3':	return 3;
		case '4':	return 4;
		case '5':	return 5;
		case '6':	return 6;
		case '7':	return 7;
		case '8':	return 8;
		case '9':	return 9;
	}
}