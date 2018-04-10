#ifndef _AUTONOMOUS_DRIVING_CONTROLLER_
#define _AUTONOMOUS_DRIVING_CONTROLLER_

class AutonomousDrivingController
{
public:
	//Constructor
	AutonomousDrivingController(ros::NodeHandle *n, GPSController *gpsController, JoystickController *joystickController, KeyboardController *keyboardController, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController);
	MovementController movementController;
	VisionController VisionController;

	//Method where the ROS Node can be given.
	void Start();

private:
	ros::NodeHandle *nh;

	bool turningLeft;
	bool turningRight;
	bool backward;

	//All controllers for autonomous driving
};

#endif
