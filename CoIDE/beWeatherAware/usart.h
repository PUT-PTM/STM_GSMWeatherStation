#ifndef _USART_H
#define _USART_H

/**
 * UART		STM32F4xx	Description
 * --------------------------------------
 * TXD		PC11		PC11 is RX on STM
 * RXD		PC10 		PC10 is TX on STM
 * GND		GND			Ground
 */

void USART_TX_RX_GPIO_config();
void USART_config();
void USART_interrupt_config();
void USART_send_char(uint8_t data);
void USART_run_config();

#endif