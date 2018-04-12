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
    void *p = reinterpret_cast<void*>(kinect);
    return dynamic_cast<KinectController*>(p);
}

LidarController *VisionController::GetLidarController()
{
    void *p = reinterpret_cast<void*>(lidar);
    return dynamic_cast<LidarController*>(p);
}

SonarController *VisionController::GetSonarController()
{
    void * = reinterpret_cast<void*>(sonar);
    return dynamic_cast<SonarController*>(p);
}