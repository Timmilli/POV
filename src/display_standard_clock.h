#ifndef __DISPLAY_STANDARD_CLOCK_H__
#define __DISPLAY_STANDARD_CLOCK_H__

#include "clock_module.h"
#include "constants.h"

#include <avr/io.h>

void display_standard_clock(uint16_t mat[NUMBER_OF_POSITIONS],
                            clock_values_t *cv, uint8_t force_redraw);

#endif
