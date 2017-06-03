#ifndef _GSM_USART_H
#define _GSM_USART_H

/**
 * GSM		STM32F4xx	Description
 * --------------------------------------
 * TXD		PA3			PA3 is RX on STM
 * RXD		PA2 		PA2 is TX on STM
 * GND		GND			Ground
 */

void GSM_USART_TX_RX_GPIO_config();
void GSM_USART_config();
void GSM_USART_run_config();
void GSM_send_char(char c);
void GSM_send_string(const char* s);

#endif