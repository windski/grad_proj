#ifndef LIB_MOTOR_H_
#define LIB_MOTOR_H_

#include <cstdint>
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include <wiringPi.h>

using std::vector;
typedef std::unique_ptr<std::thread> ThreadPtr;

namespace driver {

class Motor {
 public:
  Motor(int a, int b, int c, int d);
  ~Motor();
  void Run(bool is_reverse = false);
  void Stop();
  void SetDelay(uint32_t delay) { delay_ = delay; }
  bool IsRunning() { return stop_; }

 private:
  void Write2Pins(uint32_t row);
  void WriteAlways(bool is_reverse);
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
  ThreadPtr thread_;
};

}  // driver

#endif  // LIB_MOTOR_H_
