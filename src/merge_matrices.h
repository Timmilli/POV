#ifndef __MERGE_MATRICES_H__
#define __MERGE_MATRICES_H__

#include "constants.h"

#include <avr/io.h>

/**
 * Merges the matrices to create the straight clock image
 * @param mat is the final matrix to be filled
 * @param hours_units
 * @param hours_tens forms the hours numbers with hours_units
 * @param minutes_units
 * @param minutes_tens forms the minutes numbers with minutes_units
 */
void merge_matrices(uint16_t mat[NUMBER_OF_POSITIONS], uint8_t hours_units,
                    uint8_t hours_tens, uint8_t minutes_units,
                    uint8_t minutes_tens);

#endif // __MERGE_MATRICES_H__
