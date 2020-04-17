#ifndef WEB_APP_CONTENT_H_
#define WEB_APP_CONTENT_H_

#include <cppcms/view.h>
#include <cppcms/form.h>
#include <string>

namespace content {

struct info_form : public cppcms::form {
  cppcms::widgets::radio motor;
  cppcms::widgets::select rate;
  cppcms::widgets::select is_reverse;
  cppcms::widgets::radio m_status;
  cppcms::widgets::submit submit;

  info_form() {
    motor.message("Select Motor Number");
    m_status.message("Run/Stop");
    is_reverse.message("Is Reverse?");
    rate.message("Set Delay.");
    submit.value("Go!");

    add(motor);
    add(rate);
    add(is_reverse);
    add(m_status);
    add(submit);

    motor.add("Motor No.1", "motor 1");
    motor.add("Motor No.2", "motor 2");
    motor.add("Motor No.3", "motor 3");
    motor.add("Motor No.4", "motor 4");
    rate.add("2ms", "2");
    rate.add("6ms", "6");
    rate.add("10ms", "10");
    rate.add("15ms", "15");
    rate.add("20ms", "20");
    rate.add("25ms", "25");
    is_reverse.add("Forward", "forward");
    is_reverse.add("Reverse", "reverse");
    m_status.add("Run", "running");
    m_status.add("Stop", "stopped");

    motor.non_empty();
    m_status.non_empty();
  }

  /*
  virtual bool validate() {
    if (!form::validate()) {
      return false;
    }

    if (marital.selected_id() != "single" && age.value() < 18) {
      marital.valid(false);
      return false;
    }

    return true;
  }
  */
};

struct message : public cppcms::base_content {
  std::string motor, m_status;
  info_form info;
};

}  // namespace content

#endif  // WEB_APP_CONTENT_H_

