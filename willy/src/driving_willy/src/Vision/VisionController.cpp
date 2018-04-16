#include "../include.h"

using namespace std;
void* kinect;
void* lidar;
void* sonar;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinect = static_cast<void*>(kinectController);
    }

    if (useLidar)
    {
        lidar = static_cast<void*>(lidarController);
    }

    if (useSonar)
    {
        sonar = static_cast<void*>(sonarController);
    }
}

KinectController *VisionController::GetKinectController()
{
    return static_cast<KinectController*>(kinect);
}

LidarController *VisionController::GetLidarController()
{
    return static_cast<LidarController*>(lidar);
}

SonarController *VisionController::GetSonarController()
{
    return static_cast<SonarController*>(sonar);
}