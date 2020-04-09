#include <iostream>
#include <future>
#include <chrono>
#include "lib/motor.h"

using driver::Motor;

int main() {
  if (wiringPiSetup() == -1) {
    std::cerr << "wiringPi setup failure\n";
    return -1;
  }

  Motor m(0, 1, 2, 3);
  auto handler = std::async(std::launch::async, [&]() {
    m.Run();
  });
  std::this_thread::sleep_for(std::chrono::seconds(3));
  auto stop_handler = std::async(std::launch::deferred, [&]() {
    m.Stop();
  });
  stop_handler.get();

  // wait for synchronous
  std::this_thread::sleep_for(std::chrono::seconds(1));

  handler = std::async(std::launch::async, [&]() {
    // reverse
    m.Run(true);
  });
  std::this_thread::sleep_for(std::chrono::seconds(3));
  m.Stop();

  return 0;
}

