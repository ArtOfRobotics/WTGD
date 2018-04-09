#ifndef _VISION_CONTROLLER_H_
#define _VISION_CONTROLLER_H_

class VisionController
{
  public:
    VisionController();
    KinectController GetKinectController();
    LidarController GetLidarController();
    SonarController GetSonarController();

  private:
    KinectController kinectController;
    LidarController lidarController;
    SonarController sonarController;

    bool useKinect;
    bool useLidar; //Not working yet
    bool useSonar; //Not working yet
};

#endif