#include "constants.h"

#include "clock_module.h"
#include "display_image.h"
#include "hall_sensor.h"
#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

void display_image(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv) {
  uint16_t datastreak = 0b0;
  /*
   * Creating the datastreak
   */
  uint32_t angle = get_current_angle();
  // Getting the hours and minutes digits
  if (angle < 360)
    datastreak = mat[angle / (360 / NUMBER_OF_POSITIONS)];
  else
    datastreak = 0;

  // Writing the datastreak
  write_datastreak(datastreak);
}
