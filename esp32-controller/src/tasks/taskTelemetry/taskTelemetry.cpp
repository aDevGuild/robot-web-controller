#include "taskTelemetry.h"

// Import External Variables //
extern Ultrasonic ultrasonic;
extern esp_websocket_client_handle_t ws_client;

void taskTelemetry(void* pvParameters) {
  for (;;) {
    char* message = uint_to_str(ultrasonic.read());
    esp_websocket_client_send_text(ws_client, message, strlen(message),
                                   portMAX_DELAY);
    free(message);

    vTaskDelay(TELEMETRY_PERIOD / portTICK_PERIOD_MS);
  }
}
