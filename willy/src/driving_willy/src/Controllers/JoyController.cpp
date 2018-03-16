#include "../include.h"

using namespace std;

WillyController willyController;
int argc;
char **argv;

JoyController::JoyController(WillyController *Controller, int argc, char **argv)
{
    willyController = Controller;
    argc = argc;
    argv = argv;
}

void JoyController::Start()
{
   char input; 

   while(true) {
       cin >> input;

       if (input.equal('q') {
           printf("Je hebt op q gedrukt!\n");
       }
       //_controller->SendCommandToArduino(Movement::GetForwardCommand());
   }
    /*
        _controller->SendCommandToArduino(Movement::GetForwardCommand());

        _controller->SendCommandToArduino(Movement::GetRightCommand());

        _controller->SendCommandToArduino(Movement::GetLeftCommand());

        _controller->SendCommandToArduino(Movement::GetBackwardCommand());

        _controller->SendCommandToArduino(Movement::GetStopCommand());

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
        }*/

    ros::Duration(1).sleep();
}