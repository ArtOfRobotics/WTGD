#ifndef _AUTONOMOUS_DRIVING_CONTROLLER_
#define _AUTONOMOUS_DRIVING_CONTROLLER_

class AutonomousDrivingController
{
  public:
	//Constructor
	AutonomousDrivingController(ros::NodeHandle *n, GPSController *gps, JoystickController *joystick, KeyboardController *keyboard, KinectController *kinect, LidarController *lidar, SonarController *sonar);

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
