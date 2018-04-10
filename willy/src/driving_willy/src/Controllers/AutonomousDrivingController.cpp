#include "../include.h"

using namespace std;

AutonomousDrivingController::AutonomousDrivingController(ros::NodeHandle *n, GPSController *gps, JoystickController *joystick, KeyboardController *keyboard, KinectController *kinect, LidarController *lidar, SonarController *sonar)
{
	nh = n;
	MovementController movingController = MovementController(n, gps, joystick, keyboard);
	VisionController visionControl = VisionController(n, kinect, lidar, sonar);

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
		keyboardController->getch();
		sonarController->CalculateMovingPossibilities();
		if (visionController->CanDriveForward == true)
		{
			movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			printf("forward\n");
		}
		else if (visionController->CanTurnRight == true && turningRight == false)
		{
			movementController->SendCommandToArduino(MovementController::GetRightCommand());
			turningRight = true;
			printf("Right\n");
		}
		else if (visionController->CanTurnLeft == true && turningLeft == false)
		{
			movementController->SendCommandToArduino(MovementController::GetLeftCommand());
			turningLeft = true;
			printf("Left\n");
		}
		else if (visionController->CanDriveBackward == true)
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
			if (visionController->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (visionController->CanTurnLeft == false)
			{
				movementController->SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningLeft = false;
		}

		if (turningRight == true)
		{
			if (visionController->CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController->SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (visionController->CanTurnRight == false)
			{
				movementController->SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningRight = false;
		}

		if (backward == true)
		{
			if (visionController->CanTurnLeft == true)
			{
				ros::Duration(3).sleep();
				movementController->SendCommandToArduino(MovementController::GetLeftCommand());
				turningLeft = true;
				backward = false;
			}
			if (visionController->CanTurnRight == true)
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
