#include "wsEventHandler.h"

// extern EngineController engine_controller;
extern QueueHandle_t movementQueue;

void wsEventHandler(void* event_handler_arg, esp_event_base_t event_base,
                    int32_t event_id, void* event_data) {
  esp_websocket_event_data_t data = *(esp_websocket_event_data_t*)event_data;

  if (data.data_len >= 2) {
    return;
  }

  switch (event_id) {
    case WEBSOCKET_EVENT_CONNECTED: {
      Serial.println("Websocket connected");
      break;
    }
    case WEBSOCKET_EVENT_DISCONNECTED: {
      Serial.println("Websocket disconnected");
      break;
    }
    case WEBSOCKET_EVENT_DATA: {
      Serial.print("Websocket data received: ");
      Serial.println(data.data_ptr);

      // Parse message type
      char message_type = data.data_ptr[0];

      Serial.print("Message type: ");
      Serial.println(message_type);

      switch (message_type) {
        case MESSAGE_TYPE_MOVE: {
          MovementRequest parsed_message;

          // Parse message specific command
          parsed_message.spec = data.data_ptr[1];

          // Movement requires at least 1 argument
          if (data.data_len <= 3) {
            Serial.println("Not enough arguments");
            return;
          }
          // Parse arguments
          size_t arg_begin = 2;
          size_t arg_end = 3;
          while (arg_begin < data.data_len) {
            bool is_arg_valid = true;
            // Find the end of the argument and check if it is valid
            while (true) {
              if ((data.data_ptr[arg_end] == MESSAGE_ARG_END) ||
                  (arg_end < data.data_len)) {
                if ((arg_end - arg_begin) <= 0) {
                  Serial.println("No more arguments");
                  is_arg_valid = false;
                  break;
                } else if ((arg_end - arg_begin) <= 1) {
                  Serial.println("Argument value is missing");
                  is_arg_valid = false;
                  break;
                }
              }
              arg_end++;
            }
            if (!is_arg_valid) {
              break;
            }

            // Parse the argument
            char arg = data.data_ptr[arg_begin];
            switch (arg) {
              case MESSAGE_ARG_TIME: {
                char* arg_value;

                memcpy(arg_value, data.data_ptr + arg_begin,
                       arg_end - arg_begin);

                parsed_message.time = str_to_uint(arg_value);

                free(arg_value);
                break;
              }
              default: {
                is_arg_valid = false;
                break;
              }
            }

            if (!is_arg_valid) {
              Serial.println("Invalid argument");
              break;
            }
            // Check if there are more arguments
            if (arg_end == data.data_len) {
              break;
            } else {
              arg_begin = arg_end + 1;
              arg_end = arg_begin + 1;
            }
          }

          if (xQueueSend(movementQueue, &parsed_message, (TickType_t)10) !=
              pdPASS) {
            Serial.println("Error: movementQueue is full");
          }

          Serial.print(" | Time: ");
          Serial.println(parsed_message.time);

          break;
        }
        case MESSAGE_TYPE_CANCEL: {
          break;
        }
        default: {
          Serial.println(
              "Invalid message type! Please, use only 1 byte characters.");
          break;
        }
      }

      break;
    }
    case WEBSOCKET_EVENT_ERROR: {
      Serial.println("Websocket error");
      break;
    }
    default: {
      break;
    }
  }
}