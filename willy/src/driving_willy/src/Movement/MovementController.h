#ifndef _MOVEMENT_CONTROLLER_H_
#define _MOVEMENT_CONTROLLER_H_

class MovementController
{
  public:
	MovementController();
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

	ros::Publisher _commandPublisher;

  private:
	bool useKeyboard;
	bool useGPS;	  //Not working yet
	bool useJoystick; //Not working yet

	//The publisher where commands can be given throught cmd_vel
};

#endif