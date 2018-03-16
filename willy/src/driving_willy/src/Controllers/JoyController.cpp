#include "../include.h"

using namespace std;

JoyController::JoyController(WillyController *Controller, int argc, char **argv)
{
}

void JoyController::Start()
{
    char input;

    while (true)
    {
        input = getch();

        if (input == 'w')
        {
            _controller->SendCommandToArduino(Movement::GetForwardCommand());
        }
        else if (input == 'a')
        {
            _controller->SendCommandToArduino(Movement::GetLeftCommand());
        }
        else if (input == 'd')
        {
            _controller->SendCommandToArduino(Movement::GetRightCommand());
        }
        else if (input == 's')
        {
            _controller->SendCommandToArduino(Movement::GetBackwardCommand());
        }
        else if (input == 'q')
        {
            _controller->SendCommandToArduino(Movement::GetStopCommand());
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

char JoyController::getch()
{
    fd_set set;
    struct timeval timeout;
    int rv;
    char buff = 0;
    int len = 1;
    int filedesc = 0;
    FD_ZERO(&set);
    FD_SET(filedesc, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 1000;

    rv = select(filedesc + 1, &set, NULL, NULL, &timeout);

    struct termios old = {0};
    if (tcgetattr(filedesc, &old) < 0)
        ROS_ERROR("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(filedesc, TCSANOW, &old) < 0)
        ROS_ERROR("tcsetattr ICANON");

    if (rv == -1)
        ROS_ERROR("select");
    else if (rv == 0)
        ROS_INFO("no_key_pressed");
    else
        read(filedesc, &buff, len);

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
        ROS_ERROR("tcsetattr ~ICANON");
    return (buff);
}