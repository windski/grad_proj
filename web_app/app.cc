#include <unordered_map>

#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "app.h"
#include "content.h"

namespace app {

std::unordered_map<std::string, int> motor_map {
  {"motor 1", 0},
  {"motor 2", 1},
  {"motor 3", 2},
  {"motor 4", 3},
};

App::App(cppcms::service &srv)
: cppcms::application(srv), motors_() {
  MotorPtr m0 = std::make_unique<Motor>(0, 1, 2, 3);
  MotorPtr m1 = std::make_unique<Motor>(4, 5, 6, 7);
  MotorPtr m2 = std::make_unique<Motor>(21, 22, 23, 24);
  MotorPtr m3 = std::make_unique<Motor>(25, 26, 27, 28);
  motors_.emplace_back(std::move(m0));
  motors_.emplace_back(std::move(m1));
  motors_.emplace_back(std::move(m2));
  motors_.emplace_back(std::move(m3));
  dispatcher().assign("", &App::Index, this);
  mapper().assign("");

}

void App::Index() {
  content::message c;
  if (request().request_method() == "POST") {
    c.info.load(context());
    if (c.info.validate()) {
      c.motor = c.info.motor.selected_id();
      c.m_status = c.info.m_status.selected_id();
      c.info.clear();

      if (c.m_status == "running") {
        RunMotor(c.motor, c.info.is_reverse.selected_id(),
                 c.info.rate.selected_id());
      } else if (c.m_status == "stopped") {
        StopMotor(c.motor);
      }
    }
  }
  render("message", c);
}

void App::RunMotor(const std::string &motor,
                   const std::string &is_reverse,
                   const std::string &delay) {
  (void)delay;
  if (is_reverse == "forward" || is_reverse.size() == 0) {
    motors_[motor_map[motor]]->Run();
  } else if (is_reverse == "reverse") {
    motors_[motor_map[motor]]->Run(true);
  }
}


void App::StopMotor(const std::string &motor) {
  motors_[motor_map[motor]]->Stop();
}

}  // namespace app

