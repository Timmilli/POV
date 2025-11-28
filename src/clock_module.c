#include "constants.h"

#include "clock_module.h"
#include "hall_sensor.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * Initailises the clock
 * @param cv the clock
 */
void clock_init(clock_values_t *cv) {
  cv->us = 0;
  cv->seconds = 59;
  cv->minutes = 59;
  cv->hours = 1;
  cv->last_update_time = 0UL;
}

uint8_t clock_elapse_time(clock_values_t *cv, int delta_us) {
  uint8_t clock_updated = 0;
  cv->us += delta_us;
  if (cv->us >= 1000000UL) {
    cv->seconds += 1;
    clock_updated += 1;
    cv->us -= 1000000UL;
  }
  if (cv->seconds >= 60) {
    cv->minutes += 1;
    clock_updated += 1;
    cv->seconds = 0;
  }
  if (cv->minutes >= 60) {
    cv->hours += 1;
    clock_updated += 1;
    cv->minutes = 0;
  }
  if (cv->hours >= 24) {
    cv->hours = 0;
    clock_updated += 1;
  }
  return clock_updated;
}

/**
 * Updates the clock, to now!
 */
uint8_t clock_update(clock_values_t *cv) {
  uint32_t current_time = micros();
  uint8_t clock_updated =
      clock_elapse_time(cv, current_time - cv->last_update_time);
  cv->last_update_time = current_time;
  return clock_updated;
}

/**
 * Sets up the current time of the clock
 * @param s the seconds
 * @param min the minutes
 * @param h the hours
 **/
void clock_set_time(clock_values_t *cv, uint8_t s, uint8_t min, uint8_t h) {
  cv->last_update_time = micros();
  cv->seconds = s;
  cv->minutes = min;
  cv->hours = h;
}

/**
 * Gets the seconds of the clock
 * @returns the seconds of the clock
 */
uint8_t clock_get_seconds(clock_values_t *cv) { return cv->seconds; }

/**
 * Gets the minutes of the clock
 * @returns the minutes of the clock
 */
uint8_t clock_get_minutes(clock_values_t *cv) { return cv->minutes; }

/**
 * Gets the hours of the clock
 * @returns the hours of the clock
 */
uint8_t clock_get_hours(clock_values_t *cv) { return cv->hours; }

/**
 * Transforms the clock values into a string
 * @param str 16-character long string with "hh:mm:ss\n" format
 */
void clock_to_string(clock_values_t *cv, char str[16]) {
  str[0] = '0' + cv->hours / 10;
  str[1] = '0' + cv->hours % 10;
  str[3] = '0' + cv->minutes / 10;
  str[4] = '0' + cv->minutes % 10;
  str[6] = '0' + cv->seconds / 10;
  str[7] = '0' + cv->seconds % 10;
}
