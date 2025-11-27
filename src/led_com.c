#include "constants.h"

#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

/**
 * Sets up the communication with the led driver
 */
void setup_led_driver_com() {
  // Setup pins in writing mode
  DDRB |= (1 << PB3) | (1 << PB5); // SDI | CLK
  DDRC |= (1 << PC1) | (1 << PC2); // OE / LE

  // Setup pins in reading mode
  DDRD &= ~(1 << PD2); // HALL
}

/**
 * Writes the datastreak
 * @param datastreak is corresponding to the decimal value of the binary
 * encoding of the leds powered on
 */
void write_datastreak(uint16_t datastreak) {
  for (int i = 0; i < 16; i++) {
    if (datastreak & (1 << i)) {
      SDI_ON;
    } else {
      SDI_OFF;
    }

    CLK_ON;
    CLK_OFF;
  }

  LE_ON;
  LE_OFF;
}

/**
 * Does a PWM to adjust the brightness
 * @param duration is the number of times the function is called making it being
 * called for (duration*101)us
 */
void pwm(uint8_t clock_duration) {
  for (int _ = 0; _ < clock_duration; _++) {
    OE_ON;
    _delay_us(100);
    OE_OFF;
    _delay_us(1);
  }
}
