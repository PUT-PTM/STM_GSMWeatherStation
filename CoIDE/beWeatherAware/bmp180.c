#include "tm_stm32f4_bmp180.h"
#include "tm_stm32f4_delay.h"
#include "bmp180.h"

TM_BMP180_t BMP180_Data;

int BMP180_temperature;
int BMP180_pressure;

void BMP180_read_data()
{
	TM_BMP180_StartTemperature(&BMP180_Data);
	Delay(BMP180_Data.Delay);

	TM_BMP180_ReadTemperature(&BMP180_Data);

	TM_BMP180_StartPressure(&BMP180_Data, TM_BMP180_Oversampling_UltraHighResolution);
	Delay(BMP180_Data.Delay);

	TM_BMP180_ReadPressure(&BMP180_Data);

	Delayms(1000);

	BMP180_temperature = BMP180_Data.Temperature;
	BMP180_pressure = BMP180_Data.Pressure / 100;
}

void BMP180_check_status()
{
	if (TM_BMP180_Init(&BMP180_Data) == TM_BMP180_Result_Ok) 
	{
		// BMP180 configured and ready to use
	} 
	else 
	{
		// BMP180 error
		while (1);
	}
}