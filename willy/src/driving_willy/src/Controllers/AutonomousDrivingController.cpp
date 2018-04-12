#include "../include.h"

using namespace std;

AutonomousDrivingController::AutonomousDrivingController()
{
	turningLeft = false;
	turningRight = false;
	backward = false;
}

void AutonomousDrivingController::Start()
{
	while (true)
	{
		//movementController.GetKeyboardController()->Start(movementController.GetKeyboardController()->getch());
		//sonarController.CalculateMovingPossibilities();

		if (sonarController.CanDriveForward == true)
		{
			movementController.SendCommandToArduino(MovementController::GetForwardCommand());
			//printf("forward\n");
		}
		else if (visionController.GetSonarController().CanTurnRight == true && turningRight == false)
		{
			movementController.SendCommandToArduino(MovementController::GetRightCommand());
			turningRight = true;
			printf("Right\n");
		}
		else if (sonarController.CanTurnLeft == true && turningLeft == false)
		{
			movementController.SendCommandToArduino(MovementController::GetLeftCommand());
			turningLeft = true;
			printf("Left\n");
		}
		else if (sonarController.CanDriveBackward == true)
		{
			movementController.SendCommandToArduino(MovementController::GetBackwardCommand());
			backward = true;
			printf("Backward\n");
		}
		else
		{
			movementController.SendCommandToArduino(MovementController::GetStopCommand());
		}

		if (turningLeft == true)
		{
			if (sonarController.CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController.SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (sonarController.CanTurnLeft == false)
			{
				movementController.SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningLeft = false;
		}

		if (turningRight == true)
		{
			if (sonarController.CanDriveForward == true)
			{
				ros::Duration(2).sleep();
				movementController.SendCommandToArduino(MovementController::GetForwardCommand());
			}
			if (sonarController.CanTurnRight == false)
			{
				movementController.SendCommandToArduino(MovementController::GetStopCommand());
			}
			turningRight = false;
		}

		if (backward == true)
		{
			if (sonarController.CanTurnLeft == true)
			{
				ros::Duration(3).sleep();
				movementController.SendCommandToArduino(MovementController::GetLeftCommand());
				turningLeft = true;
				backward = false;
			}
			if (sonarController.CanTurnRight == true)
			{
				ros::Duration(3).sleep();
				movementController.SendCommandToArduino(MovementController::GetRightCommand());
				turningRight = true;
				backward = false;
			}
		}
		ros::Duration(1).sleep();
	}
}
