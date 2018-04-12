#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void Start(char input);
  //char input;
  char getch();
  //ros::Publisher keyboard("keyboard", &message);

private:
};

#endif