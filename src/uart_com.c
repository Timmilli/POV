#include "constants.h"

#include "led_com.h"
#include "uart_com.h"
#include "uart_receive.h"
#include <avr/io.h>
#include <util/delay.h>

void uart_init(unsigned int ubrr) {
  /* Baud rate */
  UBRR0H = (ubrr >> 8);
  UBRR0L = ubrr;

  UCSR0A = 0;
  UCSR0B = 0;
  UCSR0C = 0;

  UCSR0A |= (1 << U2X0);                    // mode U2X0
  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);    // enable RX and TX
  UCSR0C &= ~(1 << USBS0);                  // stop bit
  UCSR0C &= ~((1 << UPM00) | (1 << UPM00)); // parity bit
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);  // caracter size
}
