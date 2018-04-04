#ifndef _JOY_CONTROLLER_H_
#define _JOY_CONTROLLER_H_

class JoyController
{
  public:
    //Constructor
    JoyController(WillyController *Controller, int argc, char **argv);
    void Start();

  private:
    WillyController *_controller;
    char getch();
};

#endif