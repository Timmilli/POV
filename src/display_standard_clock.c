#include "constants.h"

#include "clock_module.h"
#include "display_standard_clock.h"
#include "hall_sensor.h"
#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

#define CLOCK_FORK_THICKNESS 2
#define CLOCK_TICK_THICKNESS 2

uint16_t uint16_distance(int x, int y) {
  if (x < y) {
    return y - x;
  } else {
    return x - y;
  }
}

uint16_t draw_fork(uint32_t angle, uint32_t location, uint8_t length) {
  uint16_t res = ~0b0;
  if (uint16_distance(angle, location) < CLOCK_FORK_THICKNESS) {
    res = ~(res >> length);
    return res;
  } else {
    return 0b0;
  }
}

uint16_t draw_cadran(uint32_t angle) {
  uint16_t res = 0b001;
  if (((angle + CLOCK_TICK_THICKNESS) % 30) < CLOCK_TICK_THICKNESS * 2) {
    res |= 0b011;
  }
  if (((angle + CLOCK_TICK_THICKNESS) % 90) < CLOCK_TICK_THICKNESS * 2) {
    res |= 0b0111;
  }
  return res;
}
uint16_t draw_clock(uint32_t angle, clock_values_t *cv) {
  uint16_t datastreak = draw_cadran(angle);
  datastreak |= draw_fork(angle, (360 - clock_get_seconds(cv) * 6) % 360, 13);
  datastreak |= draw_fork(angle, (360 - clock_get_minutes(cv) * 6) % 360, 10);
  datastreak |= draw_fork(
      angle,
      (360 - (clock_get_hours(cv) % 12) * 30 - clock_get_minutes(cv) / 2) % 360,
      6);
  return datastreak;
}

void redraw_clock(uint16_t *mat, clock_values_t *cv) {
  uint8_t degrees_per_pixel = (360 / NUMBER_OF_POSITIONS);
  for (int i = 0; i < NUMBER_OF_POSITIONS; i++) {
    mat[i] = draw_clock(i * degrees_per_pixel, cv);
  }
}

void display_standard_clock(uint16_t mat[NUMBER_OF_POSITIONS],
                            clock_values_t *cv, uint8_t force_redraw) {
  uint16_t datastreak = 0b0;
  uint8_t need_redraw = clock_update(cv) || force_redraw;
  if (need_redraw) {
    redraw_clock(mat, cv);
  }
  uint32_t angle = get_current_angle(); // degree
  if (angle < 360)
    datastreak = mat[angle / (360 / NUMBER_OF_POSITIONS)];
  else
    datastreak = 0b1;
  write_datastreak(datastreak);
}
