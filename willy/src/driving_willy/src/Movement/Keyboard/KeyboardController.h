#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void KeyboardCallback(char input);
  char ReadCharacter();
  //ros::Publisher keyboard("keyboard", &message);

private:
};

#endif