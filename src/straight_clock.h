#ifndef __STRAIGHT_CLOCK_H__
#define __STRAIGHT_CLOCK_H__

#include "constants.h"

#include "clock_module.h"
#include <avr/io.h>

uint16_t straight_clock_main(uint16_t mat[NUMBER_OF_POSITIONS],
                             clock_values_t *cv, uint8_t clock_updated);

#endif // __STRAIGHT_CLOCK_H__
