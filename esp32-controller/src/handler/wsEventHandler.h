/**
 * @file wsEventHandler.h
 * @brief Handles the websocket events.
 */
#ifndef WS_EVENT_HANDLER_H
#define WS_EVENT_HANDLER_H

#include "main.h"

// Function Prototypes //
/**
 * @brief Handles the websocket events.
 * @param event The event id
 * @param event_data The event data
 * @param arg User context
 */
void wsEventHandler(void* event_handler_arg, esp_event_base_t event_base,
                    int32_t event_id, void* event_data);

#endif  // WS_EVENT_HANDLER_H