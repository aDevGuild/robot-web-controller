#include "createHttpHandlers.h"

#include "../env.h"

Ultrasonic ultrasonic(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);

void createHttpHandlers(AsyncWebServer *server) {
  server->on("/healthz", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
  });

  server->on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    String status = "Battery: " + String(analogRead(BATTERY_PIN)) + "\n";
    status += "Distance: " + String(ultrasonic.read()) + " cm";
    request->send(200, "text/plain", status);
  });
}
