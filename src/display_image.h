#ifndef __DISPLAY_IMAGE_H__
#define __DISPLAY_IMAGE_H__

#include "constants.h"

#include "clock_module.h"
#include <avr/io.h>

void display_image(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv);

#endif // __DISPLAY_IMAGE_H__
