#ifndef WEB_APP_APP_H_
#define WEB_APP_APP_H_

#include <string>
#include <vector>
#include <memory>

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>

#include "lib/motor.h"

using driver::Motor;
const int32_t MOTOR_NUMS = 4;
typedef std::unique_ptr<Motor> MotorPtr;

namespace app {

class App : public cppcms::application {
 public:
  App(cppcms::service &srv);

 private:
  void Index();
  void RunMotor(const std::string &motor,
                const std::string &is_reverse,
                const std::string &delay);
  void StopMotor(const std::string &motor);

  std::vector<MotorPtr> motors_;
};

}  // namespace app

#endif  // WEB_APP_APP_H_
