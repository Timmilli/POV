#ifndef __CLOCK_MODULE_H__
#define __CLOCK_MODULE_H__

#include "constants.h"

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
  uint32_t us;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint32_t last_update_time;
} clock_values_t;

/**
 * Initailises the clock
 * @param cv the clock
 */
void clock_init(clock_values_t *cv);

/**
 * Updates the clock, to now!
 */
uint8_t clock_update(clock_values_t *cv);

/**
 * Sets up the current time of the clock
 * @param s the seconds
 * @param min the minutes
 * @param h the hours
 **/
void clock_set_time(clock_values_t *cv, uint8_t s, uint8_t min, uint8_t h);

/**
 * Gets the seconds of the clock
 * @returns the seconds of the clock
 */
uint8_t clock_get_seconds(clock_values_t *cv);

/**
 * Gets the minutes of the clock
 * @returns the minutes of the clock
 */
uint8_t clock_get_minutes(clock_values_t *cv);

/**
 * Gets the hours of the clock
 * @returns the hours of the clock
 */
uint8_t clock_get_hours(clock_values_t *cv);

/**
 * Transforms the clock values into a string
 * @param str 16-character long string with "hh:mm:ss\n" format
 */
void clock_to_string(clock_values_t *cv, char str[16]);

#endif // __CLOCK_MODULE_H__