#ifndef __QUARTER_SELECTION_H__
#define __QUARTER_SELECTION_H__

#include "constants.h"

#include <avr/io.h>

const uint16_t *get_hu_quarter(uint8_t hours_units);
const uint16_t *get_ht_quarter(uint8_t hours_tens);
const uint16_t *get_mu_quarter(uint8_t minutes_units);
const uint16_t *get_mt_quarter(uint8_t minutes_tens);

#endif // __QUARTER_SELECTION_H__
