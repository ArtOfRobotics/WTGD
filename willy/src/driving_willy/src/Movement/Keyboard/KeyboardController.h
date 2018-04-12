#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void Start(char input, MovementController *movementController);
  //char input;
  char getch();
  //ros::Publisher keyboard("keyboard", &message);

private:
};

#endif