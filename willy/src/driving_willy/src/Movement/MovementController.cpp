#include "../include.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

using namespace std;

void *keyboard;
void *gps;
void *joystick;

//Command publisher
static ros::Publisher _commandPublisher;
static ros::Publisher keyboardPublisher;

MovementController::MovementController(ros::NodeHandle *nh, GPSController *gpsController, JoystickController *joystickController, KeyboardController *keyboardController)
{
	keyboard = static_cast<void *>(keyboardController);
	gps = static_cast<void *>(gpsController);
	joystick = static_cast<void *>(joystickController);

	keyboardPublisher = nh->advertise<std_msgs::Char>("/keyboard", 100);
	_commandPublisher = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void MovementController::SendCommandToArduino(geometry_msgs::Twist msg)
{
	_commandPublisher.publish(msg);
}

ros::Publisher MovementController::GetCommandPublisher()
{
	return _commandPublisher;
}

ros::Publisher MovementController::GetKeyboardPublisher()
{
	return keyboardPublisher;
}

void MovementController::SetupTransform()
{
	ros::Rate r(100);
	tf::TransformBroadcaster broadcaster;

	broadcaster.sendTransform(tf::StampedTransform(tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.3, 0.0, 0.0)), ros::Time::now(), "base_link", "base_laser"));
	r.sleep();
}

void MovementController::SendNavigationGoal(int x, int y)
{

	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base_simple", true);

	//wait for the action server to come up
	while (!ac.waitForServer(ros::Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = x;
	goal.target_pose.pose.position.y = y;
	goal.target_pose.pose.orientation.w = x;

	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
	{
		ROS_INFO("Hooray, the base moved 1 meter forward");
	}
	else
	{
		ROS_INFO("The base failed to move forward 1 meter for some reason");
	}
}

//Method for returning the forward command.
geometry_msgs::Twist MovementController::GetForwardCommand()
{
	geometry_msgs::Twist goForwardDriving;

	goForwardDriving.linear.x = 0.30;
	goForwardDriving.linear.y = 0;
	goForwardDriving.linear.z = 0;
	goForwardDriving.angular.x = 0;
	goForwardDriving.angular.y = 0;
	goForwardDriving.angular.z = 0;

	return goForwardDriving;
}

//Method for returning the backward command.
geometry_msgs::Twist MovementController::GetBackwardCommand()
{
	geometry_msgs::Twist goBackwardDriving;

	goBackwardDriving.linear.x = -0.30;
	goBackwardDriving.linear.y = 0;
	goBackwardDriving.linear.z = 0;
	goBackwardDriving.angular.x = 0;
	goBackwardDriving.angular.y = 0;
	goBackwardDriving.angular.z = 0;

	return goBackwardDriving;
}

//Method for returning the stop command.
geometry_msgs::Twist MovementController::GetStopCommand()
{
	geometry_msgs::Twist stopDriving;

	stopDriving.linear.x = 0;
	stopDriving.linear.y = 0;
	stopDriving.linear.z = 0;
	stopDriving.angular.x = 0;
	stopDriving.angular.y = 0;
	stopDriving.angular.z = 0;

	return stopDriving;
}

//Method for returning the left command.
geometry_msgs::Twist MovementController::GetLeftCommand()
{
	geometry_msgs::Twist leftDriving;

	leftDriving.linear.x = 0;
	leftDriving.linear.y = 0;
	leftDriving.linear.z = 0;
	leftDriving.angular.x = 0;
	leftDriving.angular.y = 0;
	leftDriving.angular.z = 0.20;

	return leftDriving;
}

//Method for returning the right command.
geometry_msgs::Twist MovementController::GetRightCommand()
{
	geometry_msgs::Twist rightDriving;

	rightDriving.linear.x = 0;
	rightDriving.linear.y = 0;
	rightDriving.linear.z = 0;
	rightDriving.angular.x = 0;
	rightDriving.angular.y = 0;
	rightDriving.angular.z = -0.40;

	return rightDriving;
}

GPSController *MovementController::GetGPSController()
{
	return static_cast<GPSController *>(gps);
}

JoystickController *MovementController::GetJoystickController()
{
	return static_cast<JoystickController *>(joystick);
}

KeyboardController *MovementController::GetKeyboardController()
{
	return static_cast<KeyboardController *>(keyboard);
}
