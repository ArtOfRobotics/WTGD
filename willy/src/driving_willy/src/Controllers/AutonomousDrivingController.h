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

	//All controllers for autonomous driving
	MovementController movementController;
	VisionController visionController;
};

#endif
