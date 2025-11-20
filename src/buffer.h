#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "constants.h"

#include <avr/io.h>

/**
 * Defines the action available from Bluetooth commands
 */
typedef enum {
  NONE = 0,     // no command, or command not recognized
  SET_HOUR = 1, // hour needs to be set according to values passed
} process_action_e;

/**
 * Defines the ring buffer structure
 */
typedef struct {
  uint8_t counter;
  uint8_t tail;
  uint8_t data[RING_BUFFER_SIZE];
} ring_buffer_t;

/**
 * Initializes the ring buffer to work as a FIFO
 * @param rb empty ring_buffer
 */
void ring_buffer_init(ring_buffer_t *rb);

/**
 * Adds a byte to the ring buffer, does not check if the buffer is full
 * @param rb non-full ring buffer
 * @param data
 */
void ring_buffer_put(ring_buffer_t *rb, uint8_t data);

/**
 * Pops a byte from the ring buffer, does not check if the buffer is empty
 * @param rb non-empty ring buffer
 * @returns the first byte of the buffer
 */
uint8_t ring_buffer_get(ring_buffer_t *rb);

/**
 * Indicates the number of bytes currently used in the ring buffer
 * @param rb a ring buffer
 * @returns the number of bytes used
 */
uint8_t ring_buffer_available_bytes(ring_buffer_t *rb);

/**
 * Indicates if the buffer is empty
 * @param rb a ring buffer
 * @returns 1 if empty, 0 otherwise
 */
uint8_t ring_buffer_is_empty(ring_buffer_t *rb);

/**
 * Indicates if the buffer is full
 * @param rb a ring buffer
 * @returns 1 if full, 0 otherwise
 */
uint8_t ring_buffer_is_full(ring_buffer_t *rb);

/**
 * Compares two strings of three characters
 * @param fstr first string to compare
 * @param sstr second string to compare
 * @returns 1 if strings are equal, 0 otherwise
 */
uint8_t str_cmp(char fstr[3], char sstr[3]);

/**
 * Processes the ring buffer bytes by returning a process_action_e value
 * indicating the data read
 * @param rb a ring buffer
 * @returns a process_action_e value
 *
 * Accepted formats :
 * - setHHMMSS ('set' then 6 digits)
 */
uint8_t process_ring_buffer(ring_buffer_t *rb);

#endif // __BUFFER_H__
