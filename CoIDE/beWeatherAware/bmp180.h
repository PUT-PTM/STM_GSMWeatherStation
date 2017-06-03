#ifndef _BMP180_H
#define _BMP180_H

/**
 * BMP180	STM32F4xx	Description
 * --------------------------------------
 * SCL		PA8			I2C3 Serial clock
 * SDA		PC9 		I2C3 Serial data
 * VIN		3			Power supply
 * GND		GND			Ground
 */

void BMP180_check_status();
void BMP180_read_data();

#endif