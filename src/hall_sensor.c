#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <time.h>

volatile uint32_t last_hall_call = 0UL;
volatile float turning_speed = 0;
volatile uint32_t timer_overflow_count = 0;

ISR(INT0_vect) {
  uint32_t current_time = micros();
  turning_speed = 1000000.0 / (float)(current_time - last_hall_call);
  last_hall_call = current_time;
}

// Interrupt Service Routine for Timer0 overflow
ISR(TIMER1_OVF_vect) { timer_overflow_count++; }

// Initialize Timer0
void init_timer() {
  TCCR1A = 0;
  TCCR1B = 0;

  // Prescaler = 8
  TCCR1B |= (1 << CS11);

  // Enable overflow interrupt
  TIMSK1 |= (1 << TOIE1);
}

void setup_hall_sensor() {
  DDRD &= ~(1 << HALL_SENSOR_PIN); // PD2 (entry)
  EICRA |= (11 << ISC00);          // set INT0 to trigger on rising
  EIMSK |= (1 << INT0);            // Turns on INT0
  init_timer();
}

// Return milliseconds since program start
uint32_t micros() {
  uint32_t overflow_count;
  uint16_t timer_count;

  // Temporarily disable interrupts to read consistent values
  cli();
  overflow_count = timer_overflow_count;
  timer_count = TCNT1;

  // Check if an overflow occurred while reading
  if ((TIFR1 & (1 << TOV1)) && (timer_count < 65535)) {
    overflow_count++;
    timer_count = TCNT1; // update timer count after overflow
  }
  sei();

  // Each tick = 0.5 µs with prescaler 8
  uint32_t micros = (overflow_count * 65536UL + timer_count) / 2;
  return micros;
}

float get_turning_speed() { return turning_speed; }

float get_current_angle() {
  return 360.0 * (get_time_since_last_hall_call() / 1000.0) *
         get_turning_speed();
}

float get_time_since_last_hall_call() {
  return ((float)(micros() - last_hall_call)) / 1000.0;
}
