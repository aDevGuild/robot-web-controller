#include "taskTelemetry.h"

// Import External Variables //
extern Ultrasonic ultrasonic;
extern esp_websocket_client_handle_t ws_client;

char ultrasonic_message[4];

void taskTelemetry(void* pvParameters) {
  for (;;) {
    ultrasonic_message[0] = MESSAGE_TYPE_TELEMETRY;
    ultrasonic_message[1] = MESSAGE_SPEC_TELEMETRY_DISTANCE;

    char* ultrasonic_v;
    ultrasonic_v = uint_to_str(ultrasonic.read());

    ultrasonic_message[2] = ultrasonic_v[0];
    ultrasonic_message[3] = ultrasonic_v[1];

    esp_websocket_client_send_text(ws_client, ultrasonic_message,
                                   strlen(ultrasonic_message), portMAX_DELAY);

    free(ultrasonic_v);
    vTaskDelay(TELEMETRY_PERIOD / portTICK_PERIOD_MS);
  }
}
