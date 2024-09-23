#include "taskMovement.h"

extern QueueHandle_t movementQueue;
extern EngineController engine_controller;

MovementRequest current_command;

void taskMovement(void* pvParameters) {
  for (;;) {
    xQueueReceive(movementQueue, &current_command, (TickType_t)10);

    switch (current_command.spec) {
      case MESSAGE_SPEC_MOVE_FORWARD: {
        engine_controller.move(255, 255);
        vTaskDelay(current_command.time);
        engine_controller.move(0, 0);
        break;
      }
      case MESSAGE_SPEC_MOVE_BACKWARD: {
        engine_controller.move(-255, -255);
        vTaskDelay(current_command.time);
        engine_controller.move(0, 0);
        break;
      }
      case MESSAGE_SPEC_MOVE_STOP: {
        engine_controller.move(0, 0);
        vTaskDelay(current_command.time);
        break;
      }
      default: {
        break;
      }
    }

    vTaskDelay(TELEMETRY_PERIOD / portTICK_PERIOD_MS);
  }
}