#include "constants.h"

#include "buffer.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void uart_init(uint32_t ubrr) {
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
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);  // character size

  UCSR0B |= (1 << RXCIE0); // interrupt on receive complete
}

void uart_send_byte(ring_buffer_t *rb) {
  /* Put data into buffer, sends the data */
  UDR0 = ring_buffer_get(rb);
}

void uart_send_string(char *str, ring_buffer_t *rb) {
  int i = 0;
  while (str[i] != '\0') {
    if (!ring_buffer_is_full(rb))
      ring_buffer_put(rb, str[i++]);
    UDRIE_INTERRUPT_ON;
  }
}

// Indique si l'UART a au moins un octet disponible
uint8_t uart_available() { return (UCSR0A & (1 << RXC0)); }

// Récupère un octet de l'UART
void uart_read_byte(ring_buffer_t *rb) {
  uint8_t data = UDR0;
  ring_buffer_put(rb, data);
}
