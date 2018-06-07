#ifndef _MOVEMENT_CONTROLLER_H_
#define _MOVEMENT_CONTROLLER_H_

using namespace std;

class MovementController
{
  public:
	MovementController(ros::NodeHandle *nh, GPSController *gpsController, JoystickController *joystickController, KeyboardController *keyboardController);
	//Method to send movement commands to arduino
	void SendCommandToArduino(geometry_msgs::Twist msg);

	//Method which returns the forward command.
	static geometry_msgs::Twist GetForwardCommand();

	//Method which returns the backward command.
	static geometry_msgs::Twist GetBackwardCommand();

	//Method which returns the stop command.
	static geometry_msgs::Twist GetStopCommand();

	//Method which returns the left command
	static geometry_msgs::Twist GetLeftCommand();

	//Method which returns the right command
	static geometry_msgs::Twist GetRightCommand();

	//Method which returns the command publisher
	static ros::Publisher GetCommandPublisher();

	static ros::Publisher GetKeyboardPublisher();

	//Method which returns the gps controller;
	GPSController *GetGPSController();

	//Method which returns the joystick controller
	JoystickController *GetJoystickController();

	//Method which returns the keyboard controller;
	KeyboardController *GetKeyboardController();

	//Method to send a navigation goal;
	void SendNavigationGoal(int x, int y);

	//Method to setup transform
	void SetupTransform();

  private:

	//The publisher where commands can be given throught cmd_vel
};

#endif