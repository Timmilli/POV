#include "constants.h"

#include "led_com.h"
#include <avr/io.h>
#include <stdlib.h>
#include <time.h>
#include <util/delay.h>

void setup_led_driver_com() {
  // Setup pins in writing mode
  DDRB |= (1 << PB3) | (1 << PB5); // SDI | CLK
  DDRC |= (1 << PC1) | (1 << PC2); // OE / LE
}

void write_datastreak(int8_t powered_led_index) {
  for (int i = 0; i < 16; i++) {
    if ((1 << powered_led_index) & (1 << i)) {
      // SDI
      // turns on
      SDI_ON;
    } else {
      // SDI
      // shuts off
      SDI_OFF;
    }

    // CLK
    // turns on
    CLK_ON;
    // CLK
    // shuts off
    CLK_OFF;
  }

  // LE
  // turns on
  LE_ON;
  // turns off
  LE_OFF;
}

void pwm(int clock_duration) {
  for (int _ = 0; _ < clock_duration; _++) {
    // OE on
    OE_ON;
    _delay_us(50);
    // OE off
    OE_OFF;
    _delay_us(0.1);
  }
}

int led_com_main(void) {
  srand(time(NULL));

  setup_led_driver_com();

  int8_t powered_led_index = 0;

  while (1) {
    pwm(500);

    write_datastreak(powered_led_index);
#ifndef USE_RANDOM
    if (powered_led_index >= 16) {
      powered_led_index = 0;
    } else {
      powered_led_index++;
    }
#else
    powered_led_index = rand() % 16;
#endif
  }
  return 1;
}
