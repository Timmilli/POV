#include "constants.h"

#include "buffer.h"
#include "clock_module.h"
#include "merge_matrices.h"
#include "quarter_selection.h"
#include "uart_com.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

void merge_matrices(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv) {
  uint8_t hours_units = cv->hours % 10;
  uint8_t hours_tens = cv->hours / 10;
  uint8_t minutes_units = cv->minutes % 10;
  uint8_t minutes_tens = cv->minutes / 10;
  const uint16_t *hu_quarter = get_hu_quarter(hours_units);
  const uint16_t *ht_quarter = get_ht_quarter(hours_tens);
  const uint16_t *mu_quarter = get_mu_quarter(minutes_units);
  const uint16_t *mt_quarter = get_mt_quarter(minutes_tens);

  for (uint8_t i = 0; i < NUMBER_OF_POSITIONS; i++) {
    mat[i] = pgm_read_word(&hu_quarter[i]) | pgm_read_word(&ht_quarter[i]) |
             pgm_read_word(&mu_quarter[i]) | pgm_read_word(&mt_quarter[i]);
  }
}
