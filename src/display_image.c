#include "constants.h"

#include "clock_module.h"
#include "display_image.h"
#include "hall_sensor.h"
#include "image.h"
#include "led_com.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

void display_image() {
  uint16_t datastreak = 0b0;
  /*
   * Creating the datastreak
   */
  uint32_t angle = get_current_angle();
  // Getting the hours and minutes digits
  if (angle < 360)
    datastreak =
        pgm_read_word(&IMAGE_PTR[angle / (360 / NUMBER_OF_POSITIONS_IMG)]);
  else
    datastreak = 0;

  // Writing the datastreak
  write_datastreak(datastreak);
}
