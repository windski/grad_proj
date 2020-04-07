#include <iostream>
#include <chrono>
#include <future>
#include "motor.h"
#include "unistd.h"

using driver::Motor;

int main(void) {
  if (wiringPiSetup() == -1) {
    std::cerr << "wiringPi setup failure\n";
    return 0;
  }
  Motor m(0, 1, 2, 3);

  auto start = std::async(std::launch::async, [&]() {
    m.Run();
  });

  auto stop_motor = std::async(std::launch::deferred, [&]() {
    m.Stop();
  });

  std::this_thread::sleep_for(std::chrono::seconds(3));
  stop_motor.get();

  return 0;
}

