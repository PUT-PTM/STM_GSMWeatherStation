#ifndef _DHT11_H
#define _DHT11_H

/**
 * DHT11	STM32F4xx	Description
 * ---------------------------------
 * OUT		PA1			OneWire
 * VCC		3V			Power supply
 * GND		GND			Ground
 */

void DHT11_TIM2_config();
void DHT11_GPIOA_output_config();
void DHT11_GPIOA_input_config();
void DHT11_delay();
void DHT11_delay(int time);
void DHT11_run_config();
int DHT11_read_data();

#endif