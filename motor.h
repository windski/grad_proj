#ifndef MOTOR_H_
#define MOTOR_H_

#include <cstdint>
#include <vector>
#include <mutex>
#include <wiringPi.h>

namespace driver {
using std::vector;

class Motor {
 public:
  Motor(int a, int b, int c, int d);
  ~Motor();
  void Run(bool is_reverse = false);
  void Stop();
  void SetDelay(uint32_t delay) { delay_ = delay; }

 private:
  void Write2Pins(uint32_t row);
  void WriteOnce(bool is_reverse);
  void Fill2Values() {
    for (uint32_t i = 0; i < values_.size(); i++) {
      for (uint32_t j = 0; j < values_.size(); j++) {
        if (i == j) {
          values_[i][j] = HIGH;
        }
      }
    }
  }

  vector<int> pins_;
  vector<vector<uint32_t>> values_;
  uint32_t delay_;
  bool stop_;
  std::mutex mutex_;
};

}  // driver

#endif  // MOTOR_H_
