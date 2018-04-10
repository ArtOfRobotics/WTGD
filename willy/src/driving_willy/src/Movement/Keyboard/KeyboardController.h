#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void Start();
  char message;
  //ros::Publisher keyboard("keyboard", &message);

private:
  void getch();
};

#endif