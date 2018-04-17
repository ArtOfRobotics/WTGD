#include "../../include.h"

using namespace std;

JoystickController::JoystickController() : linear_(1),
                                           angular_(2)
{
    //MovementController::GetNodeHandler()->param("axis_linear", linear_, linear_);
    //MovementController::GetNodeHandler()->param("axis_angular", angular_, angular_);
    //MovementController::GetNodeHandler()->param("scale_angular", a_scale_, a_scale_);
    //MovementController::GetNodeHandler()->param("scale_linear", l_scale_, l_scale_);

    //http://wiki.ros.org/joy/Tutorials/ConfiguringALinuxJoystick
    printf("Er is een nieuwe Joystick controller aangemaakt!\n");
}

void JoystickController::JoystickCallback(const sensor_msgs::Joy::ConstPtr &msg)
{
    printf("Received joystick data!\n");
    //geometry_msgs::Twist twist;
    //twist.angular.z = a_scale_ * msg->axes[angular_];
    //twist.linear.x = l_scale_ * msg->axes[linear_];
    for(i=0; i < msg->buttons.size(); i++) {
		ROS_INFO_STREAM("button " << i << " " << msg->buttons[i]);
    }

    //if (msg->buttons == PS3_AXIS_BUTTON_CROSS_UP) {
    //    MovementController::GetCommandPublisher().publish(MovementController::GetForwardCommand());
    //}

    //MovementController::GetCommandPublisher().publish(twist);
}
