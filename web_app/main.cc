#include <iostream>
#include <wiringPi.h>
#include "app.h"

int main(int argc, char **argv) {
  if (wiringPiSetup() == -1) {
    std::cerr << "WirgingPi Setup failure\n";
    return -1;
  }

  try {
    cppcms::service srv(argc, argv);
    srv.applications_pool().mount(cppcms::applications_factory<app::App>());
    srv.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

}

