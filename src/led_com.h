#ifndef __LED_COM_H__
#define __LED_COM_H__

#include "constants.h"

#include <avr/io.h>

int led_com_main(void);
void setup_led_driver_com();
void write_datastreak(uint16_t);
void pwm(int clock_duration);

#endif // __LED_COM_H__
