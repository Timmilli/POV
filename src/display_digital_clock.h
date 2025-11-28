#ifndef __DISPLAY_DIGITAL_CLOCK_H__
#define __DISPLAY_DIGITAL_CLOCK_H__

#include "clock_module.h"
#include "constants.h"

#include <avr/io.h>

int display_digital_clock(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv,
                          uint8_t force_redraw);

#endif