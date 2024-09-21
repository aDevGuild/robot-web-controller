#include "taskTelemetry.h"

// Import External Variables //
extern Ultrasonic ultrasonic;
extern esp_websocket_client_handle_t ws_client;

char* ultrasonic_message;
char* ultrasonic_v;

void taskTelemetry(void* pvParameters) {
  for (;;) {
    ultrasonic_message[0] = MESSAGE_TYPE_TELEMETRY;
    ultrasonic_message[1] = MESSAGE_SPEC_TELEMETRY_DISTANCE;
    ultrasonic_message[2] = '\0';

    ultrasonic_v = uint_to_str(ultrasonic.read());

    strcat(ultrasonic_message, ultrasonic_v);

    esp_websocket_client_send_text(ws_client, ultrasonic_message,
                                   strlen(ultrasonic_message), portMAX_DELAY);

    vTaskDelay(TELEMETRY_PERIOD / portTICK_PERIOD_MS);
  }
}
