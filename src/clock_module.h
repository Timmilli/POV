#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * Updates the clock, to now!
 */
void clock_update();

/**
 * Sets up the current time of the clock
 * @param s the seconds
 * @param min the minutes
 * @param h the hours
 **/
void clock_set_time(uint8_t s, uint8_t min, uint8_t h);

/**
 * Gets the seconds of the clock
 * @returns the seconds of the clock
 */
uint8_t clock_get_seconds();

/**
 * Gets the minutes of the clock
 * @returns the minutes of the clock
 */
uint8_t clock_get_minutes();

/**
 * Gets the hours of the clock
 * @returns the hours of the clock
 */
uint8_t clock_get_hours();

/**
 * Transforms the clock values into a string
 * @param str 16-character long string with "hh:mm:ss\n" format
 */
void clock_to_string(char str[16]);
