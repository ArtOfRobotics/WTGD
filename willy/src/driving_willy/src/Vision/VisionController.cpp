#include "../include.h"

using namespace std;
uintptr_t kinect;
uintptr_t lidar;
uintptr_t sonar;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinect = reinterpret_cast<uintptr_t>(kinectController);
    }

    if (useLidar)
    {
        lidar = reinterpret_cast<uintptr_t>(lidarController);
    }

    if (useSonar)
    {
        sonar = reinterpret_cast<uintptr_t>(sonarController);
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