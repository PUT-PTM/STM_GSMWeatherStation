#ifndef _LCD_H
#define _LCD_H

/**
 * LCD		STM32F4xx		Description
 * ---------------------------------------------------------------------------------------------
 * GND		GND				Ground
 * VCC		5V				Power supply for LCD
 * V0		Potentiometer 	Contrast voltage. Connect to potentiometer
 * RS 		PB2				Register select, can be overwritten in your project’s defines.h file
 * RW		GND				Read/write
 * E		PB7				Enable pin, can be overwritten in your project’s defines.h file
 * D0		-				Data 0 – doesn’t care
 * D1		-				Data 1 – doesn’t care
 * D2		-				Data 2 – doesn’t care
 * D3		-				Data 3 – doesn’t  care
 * D4		PC12			Data 4, can be overwritten in your project’s defines.h file
 * D5		PC13			Data 5, can be overwritten in your project’s defines.h file
 * D6 		PB12			Data 6, can be overwritten in your project’s defines.h file
 * D7		PB13			Data 7, can be overwritten in your project’s defines.h file
 * A		3V				Backlight positive power
 * K		GND				Ground for backlight
 */

void LCD_run_config();
void LCD_display();

#endif