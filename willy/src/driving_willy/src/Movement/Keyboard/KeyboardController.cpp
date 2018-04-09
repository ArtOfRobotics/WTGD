#include "../../include.h"

using namespace std;

KeyboardController::KeyboardController(*AutonomousDrivingController controller)
{
    autonomousDrivingController = controller;
}

void KeyboardController::Start()
{
    char input;
    bool inMenu;
    int menuItem = 0;
    printf("Starting joycontroller\n");

    while (true)
    {
        //printf("Getting character...\n");
        input = getch();
        //printf("Got a character!!!\n");

        if (input == 'w' && inMenu == false)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());
            printf("vooruit");
        }
        else if (input == 'a' && inMenu == false)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetLeftCommand());
            printf("links");
        }
        else if (input == 'd' && inMenu == false)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetRightCommand());
            printf("Rechts");
        }
        else if (input == 's' && inMenu == false)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetBackwardCommand());
            printf("Achteruit");
        }
        else if (input == 'q' && inMenu == false)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetStopCommand());
            printf("Stoppen");
        }
        else if (input == 'm' && inMenu == false)
        {
            inMenu = true;
            printf("Menu opened");
        }
        else if (input == 'n' && inMenu == true)
        {
            inMenu = false;
            menuItem = 0;
            printf("Menu closed");
        }
        else if (input == '1' && inMenu == true)
        {
            autonomousDrivingController->SendCommandToArduino(MovementController::GetStopCommand());
            menuItem = 1;
            printf("Menu 1 selected");
        }
        //autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());

        if (inMenu && menuItem > 0)
        {
            if (menuItem == 1)
            {
                printf("Running menu 1");
                autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());
                printf("Going forward\n");
                ros::Duration(2).sleep();
                autonomousDrivingController->SendCommandToArduino(MovementController::GetBackwardCommand());
                printf("Going backward\n");
                ros::Duration(2).sleep();
            }
        }
    }
    /*
        autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());

        autonomousDrivingController->SendCommandToArduino(MovementController::GetRightCommand());

        autonomousDrivingController->SendCommandToArduino(MovementController::GetLeftCommand());

        autonomousDrivingController->SendCommandToArduino(MovementController::GetBackwardCommand());

        autonomousDrivingController->SendCommandToArduino(MovementController::GetStopCommand());

        if (turningLeft == true)
        {
            if (autonomousDrivingController->CanDriveForward == true)
            {
                ros::Duration(2).sleep();
                autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());
            }
            if (autonomousDrivingController->CanTurnLeft == false)
            {
                autonomousDrivingController->SendCommandToArduino(MovementController::GetStopCommand());
            }
            turningLeft = false;
        }

        if (turningRight == true)
        {
            if (autonomousDrivingController->CanDriveForward == true)
            {
                ros::Duration(2).sleep();
                autonomousDrivingController->SendCommandToArduino(MovementController::GetForwardCommand());
            }
            if (autonomousDrivingController->CanTurnRight == false)
            {
                autonomousDrivingController->SendCommandToArduino(MovementController::GetStopCommand());
            }
            turningRight = false;
        }

        if (backward == true)
        {
            if (autonomousDrivingController->CanTurnLeft == true)
            {
                ros::Duration(3).sleep();
                autonomousDrivingController->SendCommandToArduino(MovementController::GetLeftCommand());
                turningLeft = true;
                backward = false;
            }
            if (autonomousDrivingController->CanTurnRight == true)
            {
                ros::Duration(3).sleep();
                autonomousDrivingController->SendCommandToArduino(MovementController::GetRightCommand());
                turningRight = true;
                backward = false;
            }
        }*/

    ros::Duration(1).sleep();
}

char KeyboardController::getch()
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
    //else if (rv == 0)
    //ROS_INFO("no_key_pressed");
    else
        read(filedesc, &buff, len);

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
        ROS_ERROR("tcsetattr ~ICANON");
    return (buff);
}