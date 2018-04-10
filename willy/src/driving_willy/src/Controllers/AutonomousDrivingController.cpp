#include "../include.h"

using namespace std;

AutonomousDrivingController::AutonomousDrivingController(ros::NodeHandle *n, GPSController *gps, JoystickController *joystick, KeyboardController *keyboard, KinectController *kinect, LidarController *lidar, SonarController *sonar)
{
	nh = n;
	MovementController movingController = MovementController(n, &gps, &joystick, &keyboard, &this);
	VisionController visionControl = VisionController(n, &kinect, &lidar, &sonar, &this);

	movementController = &movingController;
	visionController = &visionControl;

	gpsController = gps;
	joystickController = joystick;
	keyboardController = keyboard;
	kinectController = kinect;
	lidarController = lidar;
	sonarController = sonar;

	turningLeft = false;
	turningRight = false;
	backward = false;
}

void AutonomousDrivingController::Start()
{
	while (true)
	{
		keyboardController->getch(nh);
		sonarController->CalculateMovingPossibilities();
		if (movementController->CanDriveForward == true)
		{
			movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			printf("forward\n");
		}
		else if (movementController->CanTurnRight == true && turningRight == false)
		{
			movementController->SendCommandToArduino(MovementController::GetRightCommand());
			turningRight = true;
			printf("Right\n");
		}
		else if (movementController->CanTurnLeft == true && turningLeft == false)
		{
			movementController->SendCommandToArduino(MovementController::GetLeftCommand());
			turningLeft = true;
			printf("Left\n");
		}
		else if (movementController->CanDriveBackward == true)
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
			if (movementController->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (movementController->CanTurnLeft == false)
			{
				movementController->SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningLeft = false;
		}

		if (turningRight == true)
		{
			if (movementController->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (movementController->CanTurnRight == false)
			{
				movementController->SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningRight = false;
		}

		if (backward == true)
		{
			if (movementController->CanTurnLeft == true)
			{
				ros::Duration(3).sleep();
				movementController->SendCommandToArduino(MovementController::GetLeftCommand());
				turningLeft = true;
				backward = false;
			}
			if (movementController->CanTurnRight == true)
			{
				ros::Duration(3).sleep();
				movementController->SendCommandToArduino(MovementController::GetRightCommand());
				turningRight = true;
				backward = false;
			}
		}

		ros::Duration(1).sleep();
	}
}
