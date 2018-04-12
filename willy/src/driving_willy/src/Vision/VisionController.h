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
  KinectController* kinect;
  LidarController* lidar;
  SonarController* sonar;

  bool useKinect;
  bool useLidar; //Not working yet
  bool useSonar; //Not working yet
};

#endif