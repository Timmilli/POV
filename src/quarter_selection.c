#include "constants.h"

#include "encoding_360.h"
#include "quarter_selection.h"
#include <avr/io.h>

/**
 * Gets the pointer to the hour units quarter according to the given value
 * @param hours_units is the value to be shown in the top right quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_hu_quarter(uint8_t hour_units) {
  switch (hour_units) {
  case 0:
    return C2N0;
  case 1:
    return C2N1;
  case 2:
    return C2N2;
  case 3:
    return C2N3;
  case 4:
    return C2N4;
  case 5:
    return C2N5;
  case 6:
    return C2N6;
  case 7:
    return C2N7;
  case 8:
    return C2N8;
  case 9:
    return C2N9;
  }
  return C2N0;
}

/**
 * Gets the pointer to the hour tens quarter according to the given value
 * @param hour_tens is the value to be shown in the top left quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_ht_quarter(uint8_t hour_tens) {
  switch (hour_tens) {
  case 0:
    return C1N0;
  case 1:
    return C1N1;
  case 2:
    return C1N2;
  }
  return C1N0;
}

/**
 * Gets the pointer to the minute units quarter according to the given value
 * @param minute_units is the value to be shown in the bottom right quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_mu_quarter(uint8_t minute_units) {
  switch (minute_units) {
  case 0:
    return C4N0;
  case 1:
    return C4N1;
  case 2:
    return C4N2;
  case 3:
    return C4N3;
  case 4:
    return C4N4;
  case 5:
    return C4N5;
  case 6:
    return C4N6;
  case 7:
    return C4N7;
  case 8:
    return C4N8;
  case 9:
    return C4N9;
  }
  return C4N0;
}

/**
 * Gets the pointer to the minute units quarter according to the given value
 * @param minute_tens is the value to be shown in the bottom left quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_mt_quarter(uint8_t minute_tens) {
  switch (minute_tens) {
  case 0:
    return C3N0;
  case 1:
    return C3N1;
  case 2:
    return C3N2;
  case 3:
    return C3N3;
  case 4:
    return C3N4;
  case 5:
    return C3N5;
  }
  return C3N0;
}
