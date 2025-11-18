#include "constants.h"

#include "hall_sensor.h"
#include "led_com.h"

#include <avr/io.h>
#include <util/delay.h>

uint32_t us = 0;
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;

uint32_t last_update_time = 0UL;

void clock_elapse_time(int delta_us) {
  us += delta_us;
  if (us >= 1000000UL) {
    seconds += 1UL;
    us -= 1000000UL;
  }
  if (seconds >= 60UL) {
    minutes += 1UL;
    seconds -= 60UL;
  }
  if (minutes >= 60UL) {
    hours += 1UL;
    minutes -= 60L;
  }
  if (hours >= 24) {
    hours -= 24;
  }
}

void clock_update() {
  uint32_t current_time = micros();
  clock_elapse_time(current_time - last_update_time);
  last_update_time = current_time;
}

uint32_t clock_get_seconds() { return seconds; }

uint32_t clock_get_minutes() { return minutes; }

uint32_t clock_get_hours() { return hours; }

void clock_set_time(long s, long min, long h) {
  last_update_time = micros();
  seconds = s;
  minutes = min;
  hours = h;
}
