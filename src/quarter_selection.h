#ifndef __QUARTER_SELECTION_H__
#define __QUARTER_SELECTION_H__

#include "constants.h"

#include <avr/io.h>

/**
 * Gets the pointer to the hour units quarter according to the given value
 * @param hours_units is the value to be shown in the top right quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_hu_quarter(uint8_t hour_units);

/**
 * Gets the pointer to the hour tens quarter according to the given value
 * @param hour_tens is the value to be shown in the top left quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_ht_quarter(uint8_t hour_tens);

/**
 * Gets the pointer to the minute units quarter according to the given value
 * @param minute_units is the value to be shown in the bottom right quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_mu_quarter(uint8_t minute_units);

/**
 * Gets the pointer to the minute units quarter according to the given value
 * @param minute_tens is the value to be shown in the bottom left quarter
 * @returns a pointer to the array corresponding to the value
 */
const uint16_t *get_mt_quarter(uint8_t minute_tens);

#endif // __QUARTER_SELECTION_H__
