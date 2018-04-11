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
        *kinectController = new KinectController();
        kinect = *kinectController;
    }

    if (useLidar)
    {
        *lidarController = new LidarController();
        lidar = *lidarController;
    }

    if (useSonar)
    {
        *sonarController = new SonarController();
        //sonar = *sonarController;
    }
}

KinectController* VisionController::GetKinectController()
{
    return &kinect;
}

LidarController* VisionController::GetLidarController()
{
    return &lidar;
}

SonarController* VisionController::GetSonarController()
{
    return &sonar;
}