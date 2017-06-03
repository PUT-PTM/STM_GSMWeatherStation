#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"

#include "lcd.h"

extern int DHT11_temperature;
extern int DHT11_humidity;
extern int BMP180_pressure;

extern int tempReceived;
extern int pressReceived;
extern int humiReceived;

int i = 0;

void LCD_run_config()
{
	uint8_t customChar[] = {
		0x1F,    // xxx 11111
		0x11,    // xxx 10001
		0x11,    // xxx 10001
		0x11,    // xxx 10001
		0x11,    // xxx 10001
		0x11,    // xxx 10001
		0x11,    // xxx 10001
		0x1F    // xxx 11111
    };
	
	TM_HD44780_Init(16, 2);
	TM_HD44780_CreateChar(0, &customChar[0]);
}

void LCD_display()
{
	if (i == 0)
	{
		i++;
		char buffer[16];
		TM_HD44780_Clear();
		sprintf(buffer, "T:%d P:%d H:%d", DHT11_temperature, BMP180_pressure, DHT11_humidity);
		TM_HD44780_Puts(0, 0, "Inside:");
		TM_HD44780_Puts(0, 1, buffer);
	}
	else
	{
		i = 0;
		char buffer[16];
		TM_HD44780_Clear();
		sprintf(buffer, "T:%d P:%d H:%d", tempReceived, pressReceived, humiReceived);
		TM_HD44780_Puts(0, 0, "Outside:");
		TM_HD44780_Puts(0, 1, buffer);
	}
}