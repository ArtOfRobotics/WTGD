#ifndef _DRIVING_CONTROLLER_
#define _DRIVING_CONTROLLER_

class DrivingController
{
  public:
	//Constructor
	DrivingController(ros::NodeHandle *n, GPSController *gps, JoystickController *joystick, KeyboardController *keyboard, KinectController *kinect, LidarController *lidar, SonarController *sonar, LightController *light, LedController *led);

	//Method where the ROS Node can be given.
	void Start();

	MovementController *movementController;
	VisionController *visionController;
	GeneralController *generalController;

  private:
	ros::NodeHandle *nh;
	bool turningLeft;
	bool turningRight;
	bool backward;

	//All controllers for autonomous driving
};

#endif