#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

uint32_t us = 0;
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;

uint32_t last_update_time = 0UL;

void clock_elapse_time(int delta_us) {
  us += delta_us;
  if (us >= 1000000UL) {
    seconds += 1UL;
    us -= 1000000UL;
  }
  if (seconds >= 60UL) {
    minutes += 1UL;
    seconds -= 60UL;
  }
  if (minutes >= 60UL) {
    hours += 1UL;
    minutes -= 60L;
  }
  if (hours >= 24) {
    hours -= 24;
  }
}

/**
 * Updates the clock, to now!
 */
void clock_update() {
  uint32_t current_time = micros();
  clock_elapse_time(current_time - last_update_time);
  last_update_time = current_time;
}

/**
 * Sets up the current time of the clock
 * @param s the seconds
 * @param min the minutes
 * @param h the hours
 **/
void clock_set_time(uint8_t s, uint8_t min, uint8_t h) {
  last_update_time = micros();
  seconds = s;
  minutes = min;
  hours = h;
}

/**
 * Gets the seconds of the clock
 * @returns the seconds of the clock
 */
uint32_t clock_get_seconds() { return seconds; }

/**
 * Gets the minutes of the clock
 * @returns the minutes of the clock
 */
uint32_t clock_get_minutes() { return minutes; }

/**
 * Gets the hours of the clock
 * @returns the hours of the clock
 */
uint32_t clock_get_hours() { return hours; }

/**
 * Transforms the clock values into a string
 * @param str 16-character long string with "hh:mm:ss\n" format
 */
void clock_to_string(char str[16]) {
  str[0] = '0' + hours / 10;
  str[1] = '0' + hours % 10;
  str[3] = '0' + minutes / 10;
  str[4] = '0' + minutes % 10;
  str[6] = '0' + seconds / 10;
  str[7] = '0' + seconds % 10;
}
