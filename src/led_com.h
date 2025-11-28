#ifndef __LED_COM_H__
#define __LED_COM_H__

#include "constants.h"

#include <avr/io.h>

/**
 * Sets up the communication with the led driver
 */
void setup_led_driver_com();

/**
 * Writes the datastreak
 * @param datastreak is corresponding to the decimal value of the binary
 * encoding of the leds powered on
 */
void write_datastreak(uint16_t datastreak);

/**
 * Does a PWM to adjust the brightness
 * @param duration is the number of times the function is called making it being
 * called for (duration*101)us
 */
void pwm(uint8_t clock_duration);

#endif // __LED_COM_H__
