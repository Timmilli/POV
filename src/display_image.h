#ifndef __DISPLAY_IMAGE_H__
#define __DISPLAY_IMAGE_H__

#include "constants.h"

#include "clock_module.h"
#include <avr/io.h>

void display_image(clock_values_t *cv, uint8_t accelerated);

#endif // __DISPLAY_IMAGE_H__
