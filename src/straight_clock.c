#include "constants.h"

#include "clock_module.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "merge_matrices.h"
#include "straight_clock.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t mat[NUMBER_OF_POSITIONS] = {};

void create_straight_clock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  uint8_t hours_tens = hours / 10;
  uint8_t hours_units = hours % 10;
  uint8_t minutes_tens = minutes / 10;
  uint8_t minutes_units = minutes % 10;

  merge_matrices(mat, hours_units, hours_tens, minutes_units, minutes_tens);
}

int straight_clock_main() {
  srand(time(NULL));
  setup_hall_sensor();
  setup_led_driver_com();
  uint16_t datastreak = 0b0000000000000000;
  clock_set_time(0, 0, 0);

  while (1) { // Main loop
    clock_update();
    uint32_t angle = get_current_angle();
    write_datastreak(mat[angle % 60]);
  }
  return 1;
}
