#include "../include.h"
#include <math.h>
#include <cmath>
#define earthRadiusMeters 6371000 //meters

AutonomousDrivingController::AutonomousDrivingController(ros::NodeHandle *n)
{
	nh = n;
	visionController = VisionController();
	movementController = MovementController();
}

bool turningLeft = false;
bool turningRight = false;
bool backward = false;

void AutonomousDrivingController::Execute(ICommand &command)
{
	command.Execute();
}

//This method receives the ROS NodeHandle and creates a new publisher
void AutonomousDrivingController::SetNode(ros::NodeHandle *n)
{
	_commandPublisher = n->advertise<geometry_msgs::Twist>("/cmd_vel", 100);
}

void AutonomousDrivingController::SendCommandToArduino(geometry_msgs::Twist msg)
{
	_commandPublisher.publish(msg);
}

void AutonomousDrivingController::Start()
{
	getRouteFromParam();
	while (true)
	{
		movementController.GetSonarController->CalculateMovingPossibilities();
		if (movementController.CanDriveForward == true)
		{
			movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			printf("forward\n");
		}
		else if (movementController.CanTurnRight == true && turningRight == false)
		{
			movementController->SendCommandToArduino(MovementController::GetRightCommand());
			turningRight = true;
			printf("Right\n");
		}
		else if (movementController.CanTurnLeft == true && turningLeft == false)
		{
			movementController->SendCommandToArduino(MovementController::GetLeftCommand());
			turningLeft = true;
			printf("Left\n");
		}
		else if (movementController.CanDriveBackward == true)
		{
			movementController->SendCommandToArduino(MovementController::GetBackwardCommand());
			backward = true;
			printf("Backward\n");
		}
		else
		{
			movementController->SendCommandToArduino(MovementController::GetStopCommand());
		}

		if (turningLeft == true)
		{
			if (_controller->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				_controller->SendCommandToArduino(Movement::GetForwardCommand());
			}
			if (_controller->CanTurnLeft == false)
			{
				_controller->SendCommandToArduino(Movement::GetStopCommand());
			}
			turningLeft = false;
		}

		if (turningRight == true)
		{
			if (_controller->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				_controller->SendCommandToArduino(Movement::GetForwardCommand());
			}
			if (_controller->CanTurnRight == false)
			{
				_controller->SendCommandToArduino(Movement::GetStopCommand());
			}
			turningRight = false;
		}

		if (backward == true)
		{
			if (_controller->CanTurnLeft == true)
			{
				ros::Duration(3).sleep();
				_controller->SendCommandToArduino(Movement::GetLeftCommand());
				turningLeft = true;
				backward = false;
			}
			if (_controller->CanTurnRight == true)
			{
				ros::Duration(3).sleep();
				_controller->SendCommandToArduino(Movement::GetRightCommand());
				turningRight = true;
				backward = false;
			}
		}

		ros::Duration(1).sleep();
	}
}

MovementController *AutonomousDrivingController::getMovementController()
{
	return &movementController;
}

VisionController *AutonomousDrivingController::getVisionController()
{
	return &visionController;
}
