#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
public:
  //Constructor
  KeyboardController();
  void Start(char input);

private:
  char key;
  ros::NodeHandle nh;
  void getch();
};

#endif