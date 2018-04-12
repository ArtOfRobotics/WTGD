#include "../include.h"

using namespace std;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        this.kinect = kinectController;
    }

    if (useLidar)
    {
        this.lidar = lidarController;
    }

    if (useSonar)
    {
        this.sonar = sonarController;
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