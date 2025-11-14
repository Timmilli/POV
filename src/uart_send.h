#ifndef __UART_SEND_H__
#define __UART_SEND_H__

#include "constants.h"

#include <avr/io.h>

void uart_send_byte(uint8_t);
void uart_send_string(char *);
int uart_send_main();

#endif // __UART_SEND_H__
