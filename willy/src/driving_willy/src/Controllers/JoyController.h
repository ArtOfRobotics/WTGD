#ifndef _JOY_CONTROLLER_H_
#define _JOY_CONTROLLER_H_

using namespace std;

class JoyController
{
  public:
    //Constructor
    JoyController(WillyController *Controller, int argc, char **argv);
    void Start();

  private:
    WillyController controller;
    int argc;
    char ** argv;
};

#endif