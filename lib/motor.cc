#include "motor.h"

namespace driver {

Motor::Motor(int a, int b, int c, int d)
  : pins_({a, b, c, d}), values_(4, vector<uint32_t>(4, LOW)),
  delay_(2), stop_(true), thread_(nullptr) {
  for (auto i : pins_) {
    pinMode(i, OUTPUT);
  }
  Fill2Values();
}

Motor::~Motor() { }

void Motor::Write2Pins(uint32_t row) {
  for (uint32_t i = 0; i < pins_.size(); i++) {
    digitalWrite(pins_[i], values_[row][i]);
  }
}

void Motor::Run(bool is_reverse) {
  if (stop_) {
    std::lock_guard<std::mutex> lock(mutex_);
    stop_ = false;
  }

  thread_.reset(new std::thread(&Motor::WriteAlways, this, is_reverse));
}

void Motor::Stop() {
  if (stop_) {
    return;
  }
  std::lock_guard<std::mutex> lock(mutex_);
  stop_ = true;
  thread_->join();
  for (auto i : pins_) {
    digitalWrite(i, LOW);
  }
}

void Motor::WriteAlways(bool is_reverse) {
  while (!stop_) {
    if (is_reverse) {
      for (uint32_t i = 0; i < 4; i++) {
        Write2Pins(i);
        delay(delay_);
      }
    } else {
      uint32_t i = pins_.size();
      while (i --> 0) {
        Write2Pins(i);
        delay(delay_);
      }
    }
  }
}

}  // driver

