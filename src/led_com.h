#ifndef __LED_COM_H__
#define __LED_COM_H__

#include "constants.h"

#include <avr/io.h>

void setup_led_driver_com();
void write_datastreak(int8_t);
void pwm(int);
int led_com_main(void);

#endif // __LED_COM_H__
