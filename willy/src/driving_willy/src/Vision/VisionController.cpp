#include "../include.h"

using namespace std;
KinectController *kinect;
LidarController *lidar;
SonarController *sonar;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinect = kinectController;
    }

    if (useLidar)
    {
        lidar = lidarController;
    }

    if (useSonar)
    {
        sonar = sonarController;
    }
}

KinectController *VisionController::GetKinectController()
{
    return kinect;
}

LidarController *VisionController::GetLidarController()
{
    return lidar;
}

SonarController *VisionController::GetSonarController()
{
    return sonar;
}