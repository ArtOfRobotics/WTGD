#ifndef _KEYBOARD_CONTROLLER_H_
#define _KEYBOARD_CONTROLLER_H_

class KeyboardController
{
  public:
    //Constructor
    KeyboardController(MovementController controller);
    void Start(MovementController movementController);

  private:
    char getch();
};

#endif