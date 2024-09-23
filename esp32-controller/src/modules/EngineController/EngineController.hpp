/**
 * @file EngineController.h
 * @brief Abstraction for the engine controller.
 */
#ifndef ENGINE_CONTROLLER_HPP
#define ENGINE_CONTROLLER_HPP

#include "main.h"

/**
 * @brief Abstract a controller for a pair of engines, the minimum to move a
 * robot in 2 dimensions.
 */
class EngineController {
 private:
  uint8_t _left_forward_pin_;
  uint8_t _left_backward_pin_;
  uint8_t _right_forward_pin_;
  uint8_t _right_backward_pin_;

 public:
  /**
   * @brief Constructor.
   * @param uint8_t left_forward_pin
   * @param uint8_t left_backward_pin
   * @param uint8_t right_forward_pin
   * @param uint8_t right_backward_pin
   */
  EngineController(uint8_t left_forward_pin, uint8_t left_backward_pin,
                   uint8_t right_forward_pin, uint8_t right_backward_pin)
      : _left_forward_pin_(left_forward_pin),
        _left_backward_pin_(left_backward_pin),
        _right_forward_pin_(right_forward_pin),
        _right_backward_pin_(right_backward_pin) {}

  /**
   * @brief Move the robot engines.
   * @param int16_t left_speed - negative for backward, positive for forward
   * @param int16_t right_speed - negative for backward, positive for forward
   */
  void move(int16_t left_speed, int16_t right_speed) {
    if (left_speed > 0) {
      analogWrite(_left_forward_pin_, left_speed);
      analogWrite(_left_backward_pin_, 0);
    } else {
      analogWrite(_left_forward_pin_, 0);
      analogWrite(_left_backward_pin_, left_speed);
    }

    if (right_speed > 0) {
      analogWrite(_right_forward_pin_, right_speed);
      analogWrite(_right_backward_pin_, 0);
    } else {
      analogWrite(_right_forward_pin_, 0);
      analogWrite(_right_backward_pin_, right_speed);
    }
  }
};

#endif  // ENGINE_CONTROLLER_HPP
