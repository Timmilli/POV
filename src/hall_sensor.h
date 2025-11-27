#ifndef __HALL_SENSOR_H__
#define __HALL_SENSOR_H__

#include "constants.h"

#include <avr/io.h>

/**
 * Sets up the hall sensor
 */
void setup_hall_sensor();

/**
 * Give for how long the programm has been running in us
 */
uint32_t micros();

/**
 * Get turning speed in turn per s
 */
float get_turning_speed();

/**
 * Get current angle approximation, according to the timer and turning speed.
 */
float get_current_angle();

/**
 * Get time since the last call of this function in ms
 */
float get_time_since_last_hall_call();

#endif // __HALL_SENSOR_H__
