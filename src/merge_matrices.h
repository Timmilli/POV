#ifndef __MERGE_MATRICES_H__
#define __MERGE_MATRICES_H__

#include "constants.h"

#include "clock_module.h"
#include <avr/io.h>

/**
 * Merges the matrices to create the straight clock image
 * @param mat is the final matrix to be filled
 * @param cv the clock values to fill the matrix with
 */
void merge_matrices(uint16_t mat[NUMBER_OF_POSITIONS], clock_values_t *cv);

#endif // __MERGE_MATRICES_H__
