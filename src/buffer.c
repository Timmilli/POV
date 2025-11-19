#include "constants.h"

#include "buffer.h"
#include <avr/io.h>

/**
 * Defines the ring buffer structure
 */
struct ring_buffer {
  uint8_t head;
  uint8_t tail;
  uint8_t data[RING_BUFFER_SIZE];
};

/**
 * Initializes the ring buffer to work as a FIFO
 * @param rb empty ring_buffer
 */
void ring_buffer_init(ring_buffer_t *rb) {
  rb->tail = 0;
  rb->head = 0;
  for (uint8_t i = 0; i < RING_BUFFER_SIZE; i++)
    rb->data[i] = 0;
}

/**
 * Adds a byte to the ring buffer, does not check if the buffer is full
 * @param rb non-full ring buffer
 * @param data
 */
void ring_buffer_put(ring_buffer_t *rb, uint8_t data) {
  rb->data[rb->head] = data;
  rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
}

/**
 * Pops a byte from the ring buffer, does not check if the buffer is empty
 * @param rb non-empty ring buffer
 * @returns the first byte of the buffer
 */
uint8_t ring_buffer_get(ring_buffer_t *rb) {
  uint8_t data = rb->data[rb->tail];
  rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
  return data;
}

/**
 * Indicates the number of bytes currently used in the ring buffer
 * @param rb a ring buffer
 * @returns the number of bytes used
 */
uint8_t ring_buffer_available_bytes(ring_buffer_t *rb) {
  if (rb->head >= rb->tail) {
    return rb->head - rb->tail;
  } else {
    return RING_BUFFER_SIZE - (rb->tail - rb->head);
  }
}

/**
 * Indicates if the buffer is full
 * @param rb a ring buffer
 * @returns 1 if full, 0 otherwise
 */
uint8_t ring_buffer_is_full(ring_buffer_t *rb) {
  return ((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail;
}

/**
 * Compares two strings of three characters
 * @param fstr first string to compare
 * @param sstr second string to compare
 * @returns 1 if strings are equal, 0 otherwise
 */
uint8_t str_cmp(char fstr[3], char sstr[3]) {
  for (uint8_t i = 0; i < 3; i++) {
    if (fstr[i] != sstr[i])
      return 0;
  }
  return 1;
}

/**
 * Processes the ring buffer bytes by returning a process_action_e value
 * indicating the data read
 * @param rb a ring buffer
 * @returns a process_action_e value
 */
uint8_t process_ring_buffer(ring_buffer_t *rb) {
  if (ring_buffer_available_bytes(rb) >= 9) {
    char command[3] = "";
    for (uint8_t i = 0; i < 3; i++) {
      command[i] = ring_buffer_get(rb);
    }
    for (uint8_t i = 0; i < 6; i++) {
      ring_buffer_get(rb);
    }

    if (str_cmp(command, "set"))
      return SET_HOUR;
  }
  return NONE;
}
