#include "../include.h"

using namespace std;

WillyController controller;
int argc;
char **argv;

JoyController::JoyController(WillyController *Controller, int argc, char **argv)
{
    controller = Controller;
    argc = argc;
    argv = argv;
}

void JoyController::Start()
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <device>\n", argv[0]);
        fprintf(stderr, "Example: %s /dev/input/js0\n", argv[0]);
        exit(0);
    }

    Joystick *joy = new Joystick(argv[1]);

    while (true)
    {
        usleep(1000);
        joy->Update();

        if (joy->hasButtonUpdate())
        {
            update_buttons(joy);
        }

        if (joy->hasAxisUpdate())
        {
            update_axes(joy);
        }
    }

    return 0;
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