#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"

#include <avr/io.h>
#include <util/delay.h>

void clock_update();
/**
 * Update the clock, to now!
 */

void clock_set_time(uint32_t s, uint32_t min, uint32_t h);
/**
 * Set up the current time of the clock
 **/

uint32_t clock_get_seconds();
/**
 * Get the seconds of the clock
 */

uint32_t clock_get_minutes();
/**
 * Get the minutes of the clock
 */

uint32_t clock_get_hours();
/**
 * Get the hours of the clock
 */
