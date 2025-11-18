#include "constants.h"

#include "encoding.h"
#include "merge_matrices.h"
#include "quarter_selection.h"
#include <avr/io.h>

void merge_matrices(uint16_t mat[NUMBER_OF_POSITIONS], uint8_t hours_units,
                    uint8_t hours_tens, uint8_t minutes_units,
                    uint8_t minutes_tens) {
  const uint16_t *hu_quarter = get_hu_quarter(hours_units);
  const uint16_t *ht_quarter = get_ht_quarter(hours_tens);
  const uint16_t *mu_quarter = get_mu_quarter(minutes_units);
  const uint16_t *mt_quarter = get_mt_quarter(minutes_tens);

  for (uint8_t i = 0; i < NUMBER_OF_POSITIONS; i++) {
    mat[i] = hu_quarter[i] | ht_quarter[i] | mu_quarter[i] | mt_quarter[i];
  }
}
