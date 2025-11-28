#include "constants.h"

#include "clock_module.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "merge_matrices.h"
#include <avr/io.h>
#include <util/delay.h>

void display_digital_clock(uint16_t mat[NUMBER_OF_POSITIONS],
                           clock_values_t *cv, uint8_t force_redraw) {
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

  // Putting the seconds as the outer led ring
  uint8_t s = clock_get_seconds(cv);
  if (angle > 180) {
    if (s < (angle - 180) / 6) {
      datastreak &= ~(0b0000000000000001);
    } else {
      datastreak |= 0b0000000000000001;
    }
  } else {
    if (s > 30) {
      if ((s - 30) < angle / 6) {
        datastreak &= ~(0b0000000000000001);
      } else {
        datastreak |= 0b0000000000000001;
      }
    }
  }

  // Writing the datastreak
  write_datastreak(datastreak);

  /*
   * Updating the clock values
   */
  uint8_t clock_updated = clock_update(cv);
  if (clock_updated >= 2 ||
      force_redraw) // Check if the minutes have been updated
    merge_matrices(mat, cv);
}