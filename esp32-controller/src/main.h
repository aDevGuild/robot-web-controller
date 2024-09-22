/**
 * @file main.h
 * @brief Main header file.
 */

#ifndef MAIN_H
#define MAIN_H

// Framework Includes //
#include <Arduino.h>
#include <Ultrasonic.h>
#include <WiFi.h>
#include <esp_websocket_client.h>

// External Includes //
// #include <ESPAsyncWebServer.h>

// Internal Includes //
#include "env.h"
#include "handler/wsEventHandler.h"
#include "modules/EngineController/EngineController.hpp"
#include "tasks/taskMovement/taskMovement.h"
#include "tasks/taskTelemetry/taskTelemetry.h"
#include "utils/typeConversion.h"

// Define Constants //
#define QUEUE_SIZE 10

// Message Example: TYPE + SPEC + ARG + ARG_VALUE + ARG_2 + ARG_VALUE_2 + ...
// Inbound //

// Type: Move
// Move the robot in a given direction
#define MESSAGE_TYPE_MOVE 'm'
// Spec Move: Go forward
#define MESSAGE_SPEC_MOVE_FORWARD 'f'
// Spec Move: Go backward
#define MESSAGE_SPEC_MOVE_BACKWARD 'b'
// Spec Move: Stop the movement
#define MESSAGE_SPEC_MOVE_STOP 's'
// Arg: Time
// How long the movement will last
#define MESSAGE_ARG_TIME 't'
#define MESSAGE_ARG_SPEED 's'
#define MESSAGE_ARG_DISTANCE 'd'
#define MESSAGE_ARG_ANGLE 'a'

// Type: Cancel
// Cancel the execution of other commands and clean the respective queue
#define MESSAGE_TYPE_CANCEL 'c'

// Outbound //

// Type: Telemetry
#define MESSAGE_TYPE_TELEMETRY 't'
// Spec Telemetry: Distance from the ultrasonic sensor
#define MESSAGE_SPEC_TELEMETRY_DISTANCE 'd'

// Type: Log
#define MESSAGE_TYPE_LOG 'l'
// Type: Error
#define MESSAGE_TYPE_ERROR 'e'

// Punctuation: Message arguments separator
#define MESSAGE_ARG_SEPARATOR ','
// Punctuation: Message arguments end
#define MESSAGE_ARG_END ';'

// Type Definitions // BEGIN //
struct MovementRequest {
  char spec;
  TickType_t time;
};
// Type Definitions // END //

// Function Prototypes //

#endif  // MAIN_H
