#ifndef __ENCODING_H__
#define __ENCODING_H__

#include "constants.h"

#include <avr/io.h>

#define NUMBER_OF_POSITIONS 120

// Top left quarter
const uint16_t c1n0[NUMBER_OF_POSITIONS] PROGMEM = {0b0101011010100101011,
                                                    0b0101011010100101011};
#define C1N0 c1n0

const uint16_t c1n1[NUMBER_OF_POSITIONS] PROGMEM = {0b0101011010100101011,
                                                    0b0101011010100101011};
#define C1N1 c1n1

const uint16_t c1n2[NUMBER_OF_POSITIONS] PROGMEM = {0b0101011010100101011};
#define C1N2 c1n2

// Top right quarter
#define C2N0 c1n2
#define C2N1 c1n2
#define C2N2 c1n2
#define C2N3 c1n2
#define C2N4 c1n2
#define C2N5 c1n2
#define C2N6 c1n2
#define C2N7 c1n2
#define C2N8 c1n2
#define C2N9 c1n2

// Bottom left quarter
#define C3N0 0b1100
#define C3N1 0b1101
#define C3N2 0b1110
#define C3N3 0b1111
#define C3N4 0b0000
#define C3N5 0b0001

// Bottom right quarter
#define C4N0 0b0010
#define C4N1 0b0011
#define C4N2 0b0100
#define C4N3 0b0101
#define C4N4 0b0110
#define C4N5 0b0111
#define C4N6 0b0010
#define C4N7 0b0011
#define C4N8 0b0100
#define C4N9 0b0101

#endif // __ENCODING_H__
