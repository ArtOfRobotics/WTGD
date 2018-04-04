#ifndef _KINECT_CONTROLLER_H_
#define _KINECT_CONTROLLER_H_

using namespace std;

class KinectController
{
  public:
    //Constructor
    KinectController(WillyController *Controller, int argc, char **argv);
    void Start();

  private:
    WillyController *_controller;
};

#endif