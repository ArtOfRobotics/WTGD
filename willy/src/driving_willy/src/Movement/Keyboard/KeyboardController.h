#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void KeyboardCallback(std_msgs::Char &input);
  char ReadCharacter();

private:

};

#endif