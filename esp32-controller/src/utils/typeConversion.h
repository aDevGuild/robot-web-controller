#ifndef TYPE_CONVERSION_H
#define TYPE_CONVERSION_H

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Function Prototypes //
/**
 * @brief Converts a string (of any char bit size) to a number.
 * @tparam input_t The input type
 * @tparam output_t The output type
 * @param str The string to convert
 * @param str_size The size of the string
 * @return The number representation of the string
 */
template <typename input_t, typename output_t>
output_t str_to_number(const input_t* str, size_t str_size);

/**
 * @brief Converts a string to an unsigned integer.
 * @param str The string to convert
 * @return The unsigned integer representation of the string
 */
unsigned int str_to_uint(const char* str);

/**
 * @brief Converts an unsigned integer to a string. REQUIRES FREEING THE
 * RETURNED POINTER.
 * @param value The unsigned integer to convert
 * @return The string representation of the unsigned integer
 */
char* uint_to_str(unsigned int value);

#endif  // TYPE_CONVERSION_H