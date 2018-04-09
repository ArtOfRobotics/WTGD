#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
  public:
    //Constructor
    KeyboardController(MovementController);
    void Start(MovementController);

  private:
    char getch();
};

#endif