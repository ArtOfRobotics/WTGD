#ifndef _MOVEMENT_CONTROLLER_H_
#define _MOVEMENT_CONTROLLER_H_

class MovementController
{
  public:
	MovementController();
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

	KeyboardController *GetKeyboardController();
	GPSController *GetGPSController();
	JoystickController *GetJoystickController();

  private:
	KeyboardController keyboardController;
	GPSController gpsController;
	JoystickController joystickController;

	bool useKeyboard;
	bool useGPS;	  //Not working yet
	bool useJoystick; //Not working yet
};

#endif