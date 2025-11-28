#include "constants.h"

#include "buffer.h"
#include "clock_module.h"
#include "hall_sensor.h"
#include "led_com.h"
#include "merge_matrices.h"
#include "straight_clock.h"
#include "uart_com.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

uint16_t straight_clock_main(uint16_t mat[NUMBER_OF_POSITIONS],
                             clock_values_t *cv, uint8_t clock_updated) {
  // Creating the initial clock matrix
  if (clock_updated)
    merge_matrices(mat, cv);

  /*
   * Creating the datastreak
   */
  uint16_t datastreak = 0;
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

  return datastreak;
}
