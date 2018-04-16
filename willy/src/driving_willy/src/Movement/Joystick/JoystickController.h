#ifndef _JOYSTICK_CONTROLLER_H_
#define _JOYSTICK_CONTROLLER_H_

class JoystickController
{
  public:
    //Constructor
    JoystickController();
    void JoystickCallback(const sensor_msgs::Joy::ConstPtr &msg);
    void Move();

  private:
    int linear_, angular_;
    double l_scale_, a_scale_;
};

#endif