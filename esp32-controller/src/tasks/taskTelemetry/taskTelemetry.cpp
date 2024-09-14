#include "taskTelemetry.h"

// Import External Variables //
extern Ultrasonic ultrasonic;
extern AsyncWebSocket ws;
extern uint32_t client_id;

// uint32_t current_time = xTaskGetTickCount();

void taskTelemetry(void* pvParameters) {
  for (;;) {
    ws.text(client_id, String(ultrasonic.read()));

    vTaskDelay(TELEMETRY_PERIOD / portTICK_PERIOD_MS);
  }
}
