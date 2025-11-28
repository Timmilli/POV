#ifndef __DISPLAY_STANDARD_CLOCK_H__
#define __DISPLAY_STANDARD_CLOCK_H__

#include "constants.h"
#include "clock_module.h"

#include <avr/io.h>

int display_standard_clock(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv, uint8_t force_redraw);

#endif