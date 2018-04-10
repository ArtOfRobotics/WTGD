#ifndef _VISION_CONTROLLER_H_
#define _VISION_CONTROLLER_H_

class VisionController
{
public:
  VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController);

private:
  bool useKinect;
  bool useLidar; //Not working yet
  bool useSonar; //Not working yet
};

#endif