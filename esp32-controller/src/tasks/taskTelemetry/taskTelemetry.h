/**
 * @file taskTelemetry.h
 * @brief Task: sends telemetry data to the client.
 */

#ifndef TELEMETRY_H
#define TELEMETRY_H

// Internal Includes //
#include "main.h"

// Define Constants //
#define TELEMETRY_PERIOD 500

// Function Prototypes //
/**
 * @brief Task: sends telemetry data to the client.
 * @param void* pvParameters
 */
void taskTelemetry(void* pvParameters);

#endif  // TELEMETRY_H
