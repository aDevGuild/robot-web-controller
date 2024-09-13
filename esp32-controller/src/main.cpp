#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Ultrasonic.h>
#include <WiFi.h>

#include "./env.h"
#include "./handlers/createHttpHandlers.h"

// Import External Variables // BEGIN //
extern Ultrasonic ultrasonic;
// Import External Variables // END //

// Type Definitions // BEGIN //
enum MessageType { LED, MOVE };
// Type Definitions // END //

// Variable Definitions // BEGIN //
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
static uint32_t client_id;
// Variable Definitions // END //

// AsyncWebSocket Received Message Handler // BEGIN //
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      client_id = client->id();

      break;
    case WS_EVT_DATA: {
      MessageType message_type = (MessageType)((char)data[0] - '0');

      switch (message_type) {
        case MessageType::LED:
          digitalWrite(INFO_LED, (char)data[1] - '0');
          break;

        default:
          throw std::invalid_argument("Invalid message type");
      }
      break;
    }
    default:
      throw std::invalid_argument("Invalid event type");
  }
}
// AsyncWebSocket Received Message Handler // END //

// Arduino Framework Setup // BEGIN //
void setup() {
  // Serial communication setup // BEGIN //
  Serial.begin(115200);
  // Serial communication setup // END //

  // GPIO Setup // BEGIN //
  pinMode(INFO_LED, OUTPUT);
  digitalWrite(INFO_LED, 1);
  // GPIO Setup // END //

  // WIFI Setup // BEGIN //
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
      Serial.print("not yet connected executing ESP.restart();");
      ESP.restart();
    }
  }
  Serial.println();

  ws.onEvent(onEvent);
  server.addHandler(&ws);

  createHttpHandlers(&server);

  server.begin();

  digitalWrite(INFO_LED, 0);
  Serial.printf("Server running at IP address ");
  Serial.println(WiFi.localIP());
  // WIFI Setup // END //
}
// Arduino Framework Setup // END //

// Arduino Framework Super Loop // BEGIN //
uint32_t current_time = millis();
void loop() {
  if (current_time - millis() > 500) {
    ws.text(client_id, String(ultrasonic.read()));
    current_time = millis();
  }
}
// Arduino Framework Super Loop // END //
