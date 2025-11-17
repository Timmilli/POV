#ifndef __UART_COM_H__
#define __UART_COM_H__

#include "constants.h"

#include <avr/io.h>

// Initialise l'UART
void uart_init(uint32_t ubrr);

// Envoie un octet par UART
void uart_send_byte(uint8_t);

// Envoie une chaîne de caractère par UART
void uart_send_string(char *, struct ring_buffer *);

// Récupère un octet du buffer UART
uint8_t USART_Receive(uint8_t current_data);

// Indique si l'UART a au moins un octet disponible
uint8_t uart_available();

// Récupère un octet de l'UART
uint8_t uart_read_byte();

#endif // __UART_COM_H__
