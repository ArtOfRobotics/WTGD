#include "../include.h"

using namespace std;
void *kinect;
void *lidar;
void *sonar;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinect = reinterpret_cast<void*>(kinectController);
    }

    if (useLidar)
    {
        lidar = reinterpret_cast<void*>(lidarController);
    }

    if (useSonar)
    {
        sonar = reinterpret_cast<void*>(sonarController);
    }
}

KinectController *VisionController::GetKinectController()
{
    return dynamic_cast<KinectController*>(kinect);
}

LidarController *VisionController::GetLidarController()
{
    return dynamic_cast<LidarController*>(lidar);
}

SonarController *VisionController::GetSonarController()
{
    return dynamic_cast<SonarController*>(sonar);
}