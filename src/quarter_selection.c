#include "constants.h"

#include "encoding.h"
#include "quarter_selection.h"
#include <avr/io.h>

const uint16_t *get_hu_quarter(uint8_t hours_units) {
  switch (hours_units) {
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
}

const uint16_t *get_ht_quarter(uint8_t hours_tens) {
  switch (hours_tens) {
  case 0:
    return C2N0;
  case 1:
    return C2N1;
  case 2:
    return C2N2;
  }
}

const uint16_t *get_mu_quarter(uint8_t minutes_units) {
  switch (minutes_units) {
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
}

const uint16_t *get_mt_quarter(uint8_t minutes_tens) {
  switch (minutes_tens) {
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
  }
}
