#ifndef _VISION_CONTROLLER_H_
#define _VISION_CONTROLLER_H_

class VisionController
{
  public:
    VisionController();

  private:
    bool useKinect;
    bool useLidar; //Not working yet
    bool useSonar; //Not working yet
};

#endif