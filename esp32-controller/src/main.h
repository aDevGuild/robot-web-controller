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
#include "tasks/taskTelemetry/taskTelemetry.h"
#include "utils/typeConversion.h"

// Define Constants //
#define MESSAGE_TYPE_FORWARD 'f'
#define MESSAGE_TYPE_BACKWARD 'b'

// Function Prototypes //
/**
 * @brief Handles the websocket events.
 */
// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
//              AwsEventType type, void *arg, uint8_t *data, size_t len);

#endif  // MAIN_H
