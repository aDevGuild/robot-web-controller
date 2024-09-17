#include "typeConversion.h"

template <typename input_t, typename output_t>
output_t str_to_number(const input_t* str, size_t str_size) {
  output_t number = 0;
  for (size_t i = str_size - 1; i >= 0; i--) {
    number = number * 10 + (str[i] - 48);
  }

  return number;
}

unsigned int str_to_uint(const char* str) {
  char* endptr;
  unsigned long value;

  // Reset errno to 0 before calling strtoul
  errno = 0;

  // Convert string to unsigned long
  value = strtoul(str, &endptr, 10);

  // Check for various possible errors
  if (errno == ERANGE && value == ULONG_MAX) {
    // Value out of range for an unsigned long
    printf("Value out of range.\n");
    return 0;
  }

  if (endptr == str) {
    // No digits were found
    printf("Invalid input: No digits found.\n");
    return 0;
  }

  if (*endptr != '\0') {
    // If there are leftover characters in the string that aren't valid
    numbers printf("Invalid input: Contains non-numeric characters.\n");
    return 0;
  }

  // Check if the value fits in an unsigned int
  if (value > UINT_MAX) {
    printf("Value out of range for an unsigned int.\n");
    return 0;
  }

  return (unsigned int)value;
}

char* uint_to_str(unsigned int value) {
  // Allocate a buffer large enough to hold the string representation
  // The maximum number of characters for an unsigned int in decimal is 10 (for
  // 32-bit systems), plus one for the null terminator.
  char* buffer = (char*)malloc(
      12 * sizeof(char));  // Buffer for 10 digits + sign + null terminator

  if (buffer == NULL) {
    // Handle memory allocation failure
    return NULL;
  }

  // Convert the unsigned integer to a string
  sprintf(buffer, "%u", value);

  return buffer;
}