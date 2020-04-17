#include <string>
#include <iostream>
#include <future>
#include "menu.h"

namespace cmd {

Command::Command()
  : cli_(nullptr), motors_() {
  MotorPtr m0 = std::make_unique<Motor>(0, 1, 2, 3);
  MotorPtr m1 = std::make_unique<Motor>(4, 5, 6, 7);
  MotorPtr m2 = std::make_unique<Motor>(21, 22, 23, 24);
  MotorPtr m3 = std::make_unique<Motor>(25, 26, 27, 28);
  motors_.emplace_back(std::move(m0));
  motors_.emplace_back(std::move(m1));
  motors_.emplace_back(std::move(m2));
  motors_.emplace_back(std::move(m3));
  Setup();
  cli::SetColor();
}

Command::~Command() { }

void Command::Setup() {
  auto root_menu = std::make_unique<cli::Menu>("root");

  root_menu->Insert("run", {"motor No.", "is reverse"},
      [this](std::ostream &out, int n, const std::string &str) {
        if (n < 0 || n >= this->motors_.size()) {
          out << "Motor No. is Invaild\n";
          return;
        }

        if (this->motors_[n]->IsRunning()) {
          this->motors_[n]->Stop();
        }

        if (str == "true") {
          this->motors_[n]->Run(true);
        } else if (str == "false"){
          this->motors_[n]->Run();
        } else {
          out << "Unknown option for `reverse'\n";
        }
      },
      "Run Motor");

  root_menu->Insert("set", {"motor No.", "delay", "number"},
      [this](std::ostream &out, int idx, const std::string &option, int n) {
        if (option == "delay") {
          if (n < 0) {
            out << "Invaild number for delay\n";
            return ;
          }
          this->motors_[idx]->SetDelay(n);
        } else {
          out << "Unknown option\n";
        }
      
      }, "set delay/angle number");

  root_menu->Insert("stop", {"motor No."},
      [this](std::ostream &out, int n) {
        if (n < 0 || n >= this->motors_.size()) {
          out << "Motor No. is Invaild\n";
          return ;
        }
        this->motors_[n]->Stop();
      },
      "Stop Motor");

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
