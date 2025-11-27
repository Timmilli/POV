#ifndef __UART_COM_H__
#define __UART_COM_H__

#include "constants.h"

#include "buffer.h"
#include <avr/io.h>

/**
 * Initializes the UART communication
 */
void uart_init();

/**
 * Sends a byte by UART
 * Does not check if the UART is ready to send a byte
 * @param rb is the buffer to get the byte from
 */
void uart_send_byte(ring_buffer_t *rb);

/**
 * Sends a string by UART
 * Checks if the UART is ready to send each byte
 * @param str is the string to send
 * @param rb the buffer used to save the string
 */
void uart_send_string(char *, ring_buffer_t *);

/**
 * Checks if the UART is free to send or receive a byte
 * @returns 0 if available, 1 otherwise
 */
uint8_t uart_available();

/**
 * Reads a byte from the UART
 * @param rb is the buffer to put the read byte into
 * @returns 1 if end of string, 0 otherwise
 */
uint8_t uart_read_byte(ring_buffer_t *);

#endif // __UART_COM_H__
