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
        kinect = new KinectController();
        *kinectController = *kinect;
    }

    if (useLidar)
    {
        lidar = new LidarController();
        *lidarController = *lidar;
    }

    if (useSonar)
    {
        sonar = new SonarController();
        //*sonarController = *sonar;
    }
}

KinectController* VisionController::GetKinectController()
{
    return kinect;
}

LidarController* VisionController::GetLidarController()
{
    return lidar;
}

SonarController* VisionController::GetSonarController()
{
    return sonar;
}