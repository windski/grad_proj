#ifndef CMD_APP_MENU_H_
#define CMD_APP_MENU_H_

#include <vector>
#include <cli/cliasyncsession.h>
#include <cli/clilocalsession.h>
#include <cli/remotecli.h>
#include <cli/cli.h>
#include "lib/motor.h"

using driver::Motor;
const int32_t MOTOR_NUMS = 4;
typedef std::unique_ptr<Motor> MotorPtr;

namespace cmd {
typedef std::unique_ptr<cli::Cli> CliPtr;

class Command {
 public:
  Command();
  ~Command();
  void Run();

 private:
  void Setup();
  CliPtr cli_;
  boost::asio::io_context ios_;
  std::vector<MotorPtr> motors_;
};

}  // namespace cmd

#endif  // CMD_APP_MENU_H_
