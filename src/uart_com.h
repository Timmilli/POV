#ifndef __UART_COM_H__
#define __UART_COM_H__

#include "constants.h"

#include "buffer.h"
#include <avr/io.h>

// Initialise l'UART
void uart_init(uint32_t ubrr);

// Envoie un octet par UART
void uart_send_byte(ring_buffer_t *);

// Envoie une chaîne de caractère par UART
void uart_send_string(char *, ring_buffer_t *);

// Indique si l'UART a au moins un octet disponible
uint8_t uart_available();

// Récupère un octet de l'UART
void uart_read_byte(ring_buffer_t *);

#endif // __UART_COM_H__
