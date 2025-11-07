#include "constants.h"

#include <avr/io.h>

#define HALL_SENSOR_PIN PD2

void setup_hall_sensor() {
  DDRD &= ~(1 << HALL_SENSOR_PIN); // PD2 (entry)
}

int hall_is_triggered() {
  // returns 1 if there is a magnet
  return !(PIND & (1 << HALL_SENSOR_PIN)); // active when LOW
}
