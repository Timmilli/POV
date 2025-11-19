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
 * @datastreak uint16 corresponding to the decimal value of the binary encoding
 * of the led powered on
 */
void write_datastreak(uint16_t datastreak);

/**
 * Does a PWM to adjust the brightness
 * @duration int such as the function is called for (duration*101)us
 */
void pwm(int duration);

#endif // __LED_COM_H__
