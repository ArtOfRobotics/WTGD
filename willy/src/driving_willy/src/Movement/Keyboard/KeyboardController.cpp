#include "../../include.h"

using namespace std;

KeyboardController::KeyboardController(*MovementController controller)
{
    movementController = controller;
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
            movementController->SendCommandToArduino(MovementController::GetForwardCommand());
            printf("vooruit");
        }
        else if (input == 'a' && inMenu == false)
        {
            movementController->SendCommandToArduino(MovementController::GetLeftCommand());
            printf("links");
        }
        else if (input == 'd' && inMenu == false)
        {
            movementController->SendCommandToArduino(MovementController::GetRightCommand());
            printf("Rechts");
        }
        else if (input == 's' && inMenu == false)
        {
            movementController->SendCommandToArduino(MovementController::GetBackwardCommand());
            printf("Achteruit");
        }
        else if (input == 'q' && inMenu == false)
        {
            movementController->SendCommandToArduino(MovementController::GetStopCommand());
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
            movementController->SendCommandToArduino(MovementController::GetStopCommand());
            menuItem = 1;
            printf("Menu 1 selected");
        }
        //movementController->SendCommandToArduino(MovementController::GetForwardCommand());

        if (inMenu && menuItem > 0)
        {
            if (menuItem == 1)
            {
                printf("Running menu 1");
                movementController->SendCommandToArduino(MovementController::GetForwardCommand());
                printf("Going forward\n");
                ros::Duration(2).sleep();
                movementController->SendCommandToArduino(MovementController::GetBackwardCommand());
                printf("Going backward\n");
                ros::Duration(2).sleep();
            }
        }
    }
    /*
        movementController->SendCommandToArduino(MovementController::GetForwardCommand());

        movementController->SendCommandToArduino(MovementController::GetRightCommand());

        movementController->SendCommandToArduino(MovementController::GetLeftCommand());

        movementController->SendCommandToArduino(MovementController::GetBackwardCommand());

        movementController->SendCommandToArduino(MovementController::GetStopCommand());

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