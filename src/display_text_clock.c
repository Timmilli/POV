#include "constants.h"

#include "alphabet.h"
#include "clock_module.h"
#include "display_standard_clock.h"
#include "hall_sensor.h"
#include "led_com.h"
#include <avr/io.h>
#include <util/delay.h>

// This is the format used for the clock
char clock_str[8] = "hh:mm:ss";

#define NUMBER_OF_POSITIONS_TEXT 120

void display_string(uint8_t offset, uint16_t mat[NUMBER_OF_POSITIONS],
                    char str[8], uint8_t reversed) {
  /*
   * Display a 8 character string in the buffer
   */
  int char_index = 0;
  for (int i = offset; i < offset + 7 * 8; i += 7) {
    for (int j = 0; j < 7; j++) {
      if (reversed) {
        char c = str[char_index] - ALPHABET_UTF8_OFFSET;
        mat[(NUMBER_OF_POSITIONS_TEXT + (i + j)) % NUMBER_OF_POSITIONS_TEXT] =
            pgm_read_word(&ALPHABET_FLIPPED[7 * (c) + j]);
      } else {
        char c = str[char_index] - ALPHABET_UTF8_OFFSET;
        mat[(NUMBER_OF_POSITIONS_TEXT + 7 * 8 - (i + j)) %
            NUMBER_OF_POSITIONS_TEXT] = pgm_read_word(&ALPHABET[7 * (c) + j]);
      }
    }
    char_index += 1;
  }
}

void display_clear(uint16_t mat[NUMBER_OF_POSITIONS]) {
  /*
   * Clear the mat buffer to be all 0
   */
  for (int i = 0; i < NUMBER_OF_POSITIONS; i++) {
    mat[i] = 0b0;
  }
}

void display_text_clock(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv,
                        uint8_t force_redraw, uint8_t accelerated) {
  uint8_t need_redraw;
  if (accelerated)
    need_redraw = (clock_update(cv, accelerated) > 1) || force_redraw;
  else
    need_redraw = clock_update(cv, accelerated) || force_redraw;
  if (need_redraw) {
    display_clear(mat);
    clock_to_string(cv, clock_str);
    display_string(90, mat, " HELLO! ", 0);
    display_string(90, mat, clock_str, 1);
  }
  uint16_t datastreak = 0b0;

  uint32_t angle = get_current_angle();
  if (angle < 360)
    datastreak = mat[angle / (360 / NUMBER_OF_POSITIONS_TEXT)];
  else
    datastreak = 0;

  // Writing the datastreak
  write_datastreak(datastreak);
}
