#include <iostream>
#include "menu.h"

using cmd::Command;

int main() {
  if (wiringPiSetup() == -1) {
    std::cerr << "wiringPi setup failure\n";
    return 0;
  }

  Command cmd;
  cmd.Run();
  return 0;
}
