#include "main.h"

// Constant Definitions // BEGIN //
const esp_websocket_client_config_t ws_config = {
    .uri = WEBSOCKET_URI,
    // .port = WEBSOCKET_PORT,
};
// Constant Definitions // END //s

// Variable Definitions // BEGIN //
QueueHandle_t movementQueue;

esp_websocket_client_handle_t ws_client;

Ultrasonic ultrasonic(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);
EngineController engine_controller(MOTOR_LEFT_FORWARD, MOTOR_LEFT_BACKWARD,
                                   MOTOR_RIGHT_FORWARD, MOTOR_RIGHT_BACKWARD);
// Variable Definitions // END //

// Arduino Framework Setup // BEGIN //
void setup() {
  // Serial communication setup // BEGIN //
  Serial.begin(115200);
  // Serial communication setup // END //

  // GPIO Setup // BEGIN //
  // pinMode(INFO_LED, OUTPUT);
  // GPIO Setup // END //

  // WIFI Setup // BEGIN //
  // digitalWrite(INFO_LED, 1);
  Serial.print("Trying to connect to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int current_timer = millis();
  int connection_retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - current_timer < 500) {
      continue;
    }

    Serial.print(".");
    connection_retries++;
    current_timer = millis();

    if (connection_retries > 30) {
      Serial.println();
      Serial.print("not yet connected executing ESP.restart()");
      ESP.restart();
    }
  }
  Serial.println();
  Serial.printf("Client running at IP address ");
  Serial.println(WiFi.localIP());
  // digitalWrite(INFO_LED, 0);
  // WIFI Setup // END //

  // Websocket Setup // BEGIN //
  // digitalWrite(INFO_LED, 1);
  Serial.println("Trying to connect to the WebSocket server");

  ws_client = esp_websocket_client_init(&ws_config);
  esp_websocket_client_start(ws_client);

  esp_websocket_register_events(ws_client, WEBSOCKET_EVENT_ANY, wsEventHandler,
                                NULL);

  // current_timer = millis();
  // connection_retries = 0;
  // while (!esp_websocket_client_is_connected(ws_client)) {
  //   if (millis() - current_timer < 500) {
  //     continue;
  //   }

  //   Serial.print(".");
  //   connection_retries++;
  //   current_timer = millis();

  //   if (connection_retries > 30) {
  //     Serial.println();
  //     Serial.print("not yet connected executing ESP.restart()");
  //     ESP.restart();
  //   }
  // }
  // digitalWrite(INFO_LED, 0);
  // Websocket Setup // END //

  // Tasks Setup // BEGIN //
  xTaskCreate(taskTelemetry, "taskTelemetry", 1024, NULL, 1, NULL);
  xTaskCreate(taskMovement, "taskMovement", 1024, NULL, 1, NULL);
  // Tasks Setup // END //

  // Queue Setup // BEGIN //
  movementQueue = xQueueCreate(10, sizeof(MovementRequest));
  // Queue Setup // END //
}
// Arduino Framework Setup // END //

// Arduino Framework Super Loop // BEGIN //
void loop() { vTaskDelay(1000 / portTICK_PERIOD_MS); }
// Arduino Framework Super Loop // END //
