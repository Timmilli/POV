#include "constants.h"

#include "buffer.h"
#include "clock_module.h"
#include <avr/io.h>

/**
 * Initializes the ring buffer to work as a FIFO
 * @param rb empty ring_buffer
 */
void ring_buffer_init(ring_buffer_t *rb) {
  rb->tail = 0;
  rb->counter = 0;
  for (uint8_t i = 0; i < RING_BUFFER_SIZE; i++)
    rb->data[i] = 0;
}

/**
 * Adds a byte to the ring buffer, does not check if the buffer is full
 * @param rb non-full ring buffer
 * @param data
 * @returns 1 if end of string, 0 otherwise
 */
uint8_t ring_buffer_put(ring_buffer_t *rb, uint8_t data) {
  if (data != '\n' & data != '\r') {
    rb->data[(rb->tail + rb->counter) % RING_BUFFER_SIZE] = data;
    rb->counter = rb->counter + 1;
    return 0;
  } else {
    return 1;
  }
}

/**
 * Pops a byte from the ring buffer, does not check if the buffer is empty
 * @param rb non-empty ring buffer
 * @returns the first byte of the buffer
 */
uint8_t ring_buffer_get(ring_buffer_t *rb) {
  uint8_t data = rb->data[rb->tail];
  rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
  rb->counter -= 1;
  return data;
}

/**
 * Indicates the number of bytes currently used in the ring buffer
 * @param rb a ring buffer
 * @returns the number of bytes used
 */
uint8_t ring_buffer_available_bytes(ring_buffer_t *rb) { return rb->counter; }

/**
 * Indicates if the buffer is empty
 * @param rb a ring buffer
 * @returns 1 if empty, 0 otherwise
 */
uint8_t ring_buffer_is_empty(ring_buffer_t *rb) { return rb->counter == 0; }

/**
 * Indicates if the buffer is full
 * @param rb a ring buffer
 * @returns 1 if full, 0 otherwise
 */
uint8_t ring_buffer_is_full(ring_buffer_t *rb) {
  return rb->counter == RING_BUFFER_SIZE;
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
 *
 * Accepted formats :
 * - setHHMMSS ('set' then 6 digits)
 */
uint8_t process_ring_buffer(ring_buffer_t *rb) {
  if (ring_buffer_available_bytes(rb) >= 3) {
    char command[3] = "";
    for (uint8_t i = 0; i < 3; i++) {
      command[i] = ring_buffer_get(rb);
    }

    if (str_cmp(command, "set")) {
      return SET_HOUR;
    }

    else if (str_cmp(command, "get")) {
      return GET_HOUR;
    }

    else if (str_cmp(command, "spd")) {
      return GET_SPEED;
    }

    else if (str_cmp(command, "std")) {
      return CHANGE_MODE_STD_CLOCK;
    }

    else if (str_cmp(command, "dig")) {
      return CHANGE_MODE_DIG_CLOCK;
    }
  }
  return NONE;
}

/**
 * Updates the clock values according to the buffer values
 * @param rb the ring buffer to get the values from
 * @param cv the clock to update the values of
 */
void ring_buffer_update_clock(ring_buffer_t *rb, clock_values_t *cv) {
  uint8_t tens = ring_buffer_get(rb) - '0';
  uint8_t units = ring_buffer_get(rb) - '0';
  uint8_t h = 10 * tens + units;

  tens = ring_buffer_get(rb) - '0';
  units = ring_buffer_get(rb) - '0';
  uint8_t m = 10 * tens + units;

  tens = ring_buffer_get(rb) - '0';
  units = ring_buffer_get(rb) - '0';
  uint8_t s = 10 * tens + units;

  clock_set_time(cv, s, m, h);
}
