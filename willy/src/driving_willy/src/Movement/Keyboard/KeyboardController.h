#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
  public:
    //Constructor
    KeyboardController();
    void Start();

  private:
    char getch();
};

#endif