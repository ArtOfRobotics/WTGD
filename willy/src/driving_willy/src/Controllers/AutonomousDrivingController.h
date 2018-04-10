#ifndef _AUTONOMOUS_DRIVING_CONTROLLER_
#define _AUTONOMOUS_DRIVING_CONTROLLER_

class AutonomousDrivingController
{
  public:
	//Constructor
	AutonomousDrivingController(ros::NodeHandle *n);
	
	//Method where the ROS Node can be given.
	void SetNode(ros::NodeHandle *n);
	void Start();

  private:
	ros::NodeHandle *nh;

	bool turningLeft;
	bool turningRight;
	bool backward;

	//All controllers for autonomous driving
	KinectController kinectController;
	LidarController lidarController;
	GPSController gpsController;
	JoystickController joystickController;
	KeyboardController keyboardController;
	MovementController movementController;
	VisionController visionController;
};

#endif
