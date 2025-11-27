#include "constants.h"

#include "buffer.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

/**
 * Initializes the UART communication
 * @param ubrr is the baud rate
 */
void uart_init() {
  /* Baud rate */
  UBRR0H = (MYUBRR >> 8);
  UBRR0L = MYUBRR;

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

/**
 * Sends a byte by UART
 * Does not check if the UART is ready to send a byte
 * @param rb the buffer to get the byte from
 */
void uart_send_byte(ring_buffer_t *rb) {
  /* Put data into buffer, sends the data */
  UDR0 = ring_buffer_get(rb);
}

/**
 * Sends a string by UART
 * Checks if the UART is ready to send each byte
 * @param str is the string to send
 * @param rb the buffer used to save the string
 */
void uart_send_string(char *str, ring_buffer_t *rb) {
  int i = 0;
  while (str[i] != '\0') {
    if (!ring_buffer_is_full(rb))
      ring_buffer_put(rb, str[i++]);
    UDRIE_INTERRUPT_ON;
  }
}

/**
 * Checks if the UART is free to send or receive a byte
 * @returns 0 if available, 1 otherwise
 */
uint8_t uart_available() { return (UCSR0A & (1 << RXC0)); }

/**
 * Reads a byte from the UART
 * @param rb is the buffer to put the read byte into
 * @returns 1 if end of string, 0 otherwise
 */
uint8_t uart_read_byte(ring_buffer_t *rb) {
  uint8_t data = UDR0;
  return ring_buffer_put(rb, data);
}
