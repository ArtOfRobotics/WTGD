#include "../../include.h"

using namespace std;

KeyboardController::KeyboardController();
{
    //nh.advertise(keyboard);
    //ros::Publisher keyboard("keyboard", &key);
}

void KeyboardController::Start(char input, MovementController* movementController)
{
    bool inMenu;
    int menuItem = 0;
    ROS_INFO("Starting driving on keyboard input, with input: %c\n", input);

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
        //movementController->SendCommandToArduino(MovementController::GetStopCommand());
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
        //movementController->SendCommandToArduino(MovementController::GetStopCommand());
        menuItem = 1;
        printf("Menu 1 selected");
    }
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
    {
        ROS_ERROR("tcsetattr ~ICANON");
    }
    return buff;
    //message.echoes = buff;
    //message.echoes_length = 1;
    //keyboard.publish(&message);
}