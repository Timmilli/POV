#ifndef __DISPLAY_TEXT_CLOCK_H__
#define __DISPLAY_TEXT_CLOCK_H__

#include "clock_module.h"
#include "constants.h"

#include <avr/io.h>

void display_text_clock(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv,
                        uint8_t force_redraw, uint8_t accelerated);

#endif
