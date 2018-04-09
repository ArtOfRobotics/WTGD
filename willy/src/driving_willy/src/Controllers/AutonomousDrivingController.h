#ifndef _AUTONOMOUS_DRIVING_CONTROLLER_
#define _AUTONOMOUS_DRIVING_CONTROLLER_

class AutonomousDrivingController
{
  public:
	//Constructor
	AutonomousDrivingController(ros::NodeHandle *n);
	MovementController *getMovementController();
	VisionController *getVisionController();
	//Method where the ROS Node can be given.
	void SetNode(ros::NodeHandle *n);
	void Start();

  private:
	void SendCommandToArduino(geometry_msgs::Twist msg);
	ros::NodeHandle *nh;

	//All controllers for autonomous driving
	MovementController movementController;
	VisionController visionController;

	//The publisher where commands can be given throught cmd_vel
	ros::Publisher _commandPublisher;
};

#endif
