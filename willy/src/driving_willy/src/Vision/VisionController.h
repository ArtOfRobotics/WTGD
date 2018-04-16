#ifndef _VISION_CONTROLLER_H_
#define _VISION_CONTROLLER_H_

class VisionController
{
public:
  VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController);
  KinectController *GetKinectController();
  LidarController *GetLidarController();
  SonarController *GetSonarController();

private:
};

#endif