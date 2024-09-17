#include "wsEventHandler.h"

extern EngineController engine_controller;

void wsEventHandler(void* event_handler_arg, esp_event_base_t event_base,
                    int32_t event_id, void* event_data) {
  esp_websocket_event_data_t data = *(esp_websocket_event_data_t*)event_data;
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
      uint16_t message_type =
          ((uint16_t)data.data_ptr[0] << 8) | data.data_ptr[1];
      uint16_t parameter[4];
      for (uint8_t i = 1; i < 5; i++) {
        parameter[i] =
            ((uint16_t)data.data_ptr[2 * i] << 8) | data.data_ptr[(2 * i) + 1];
      }

      uint16_t duration = str_to_number<uint16_t, uint16_t>(parameter, 4);

      Serial.print("Message type: ");
      Serial.println(message_type);
      Serial.print(" | Duration: ");
      Serial.println(duration);

      switch (message_type) {
        case MESSAGE_TYPE_FORWARD: {
          engine_controller.move(255, 255);

          break;
        }
        case MESSAGE_TYPE_BACKWARD: {
          engine_controller.move(-255, -255);
          break;
        }
        default:
          throw std::invalid_argument("Invalid message type");
      }

      Serial.println("Websocket data received");
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