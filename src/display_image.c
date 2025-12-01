#include "constants.h"

#include "clock_module.h"
#include "display_image.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "logo_std.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

void display_image(clock_values_t *cv, uint8_t accelerated) {
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

  clock_update(cv, accelerated);
}
