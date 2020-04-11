#include <string>
#include <iostream>
#include <future>
#include "menu.h"

namespace cmd {

Command::Command()
  : cli_(nullptr), motors_() {
  MotorPtr m = std::make_unique<Motor>(0, 1, 2, 3);
  motors_.emplace_back(std::move(m));
  Setup();
  cli::SetColor();
}

Command::~Command() { }

void Command::Setup() {
  auto root_menu = std::make_unique<cli::Menu>("root");
  auto motor1 = std::make_unique<cli::Menu>("motor1");

  motor1->Insert("run", {"is reverse"},
      [this](std::ostream &out, const std::string &str) {
        if (str == "true") {
          this->motors_[0]->Run(true);
        } else if (str == "false"){
          this->motors_[0]->Run();
        } else {
          out << "Unknown option for `reverse'\n";
        }
      },
      "Motor1 run!");

  motor1->Insert("stop", [this](std::ostream &out) {
    this->motors_[0]->Stop();
  }, "Motor1 stop!");

  root_menu->Insert(std::move(motor1));

  root_menu->Insert("2", [](std::ostream &out) {
    out << "Motor1 run\n";
  }, "Select Motor No.2");

  cli_.reset(new cli::Cli(std::move(root_menu)));

  cli_->ExitAction([](auto &out) {
    out << "Bye!\n";
  });
}

void Command::Run() {
  cli::CliLocalTerminalSession lsession(*cli_, ios_, std::cout, 200);
  lsession.ExitAction([&, this](auto &out) {
    this->ios_.stop();
  });

  cli::CliTelnetServer server(ios_, 5000, *cli_);
  server.ExitAction([&, this](auto &out) {
    out << "Terminal the session!";
  });

  ios_.run();
}

}  // namespace cmd
