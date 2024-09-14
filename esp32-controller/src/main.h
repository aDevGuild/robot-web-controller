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

// External Includes //
#include <ESPAsyncWebServer.h>

// Internal Includes //
#include "env.h"
#include "handlers/createHttpHandlers.h"
#include "tasks/taskTelemetry/taskTelemetry.h"

// Function Prototypes //
/**
 * @brief Handles the websocket events.
 */
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len);

#endif  // MAIN_H