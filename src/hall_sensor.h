#ifndef __HALL_SENSOR_H__
#define __HALL_SENSOR_H__

#include "constants.h"
#include "time.h"
#include <avr/io.h>

/**
 * Sets up the hall sensor
 */
void setup_hall_sensor(void);

/**
 * Checks if the hall sensor is triggered
 * @return int 1 if triggered, 0 otherwise
 */

long micros(void);
/** 
 * Give for how long the programm has been running in us 
*/

float get_turning_speed();
/**
 * Get turning speed in turn per s
 */

float get_current_angle();
/**
 * Get current angle approximation, according to the timer and turning speed.
 */

float get_time_since_last_hall_call();
/**
 * Get time since the last call of this function in ms
 */

#endif // __HALL_SENSOR_H__