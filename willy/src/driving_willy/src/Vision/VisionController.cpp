#include "../include.h"

using namespace std;
int kinectAdress;
int lidarAdress;
int sonarAdress;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinectAdress = kinectController;
    }

    if (useLidar)
    {
        lidarAdress = lidarController;
    }

    if (useSonar)
    {
        sonarAdress = sonarController;
    }
}

KinectController *VisionController::GetKinectController()
{
    return reinterpret_cast<KinectController*>(kinectAdress);

LidarController *VisionController::GetLidarController()
{
    return reinterpret_cast<LidarController*>(lidarAdress);
}

SonarController *VisionController::GetSonarController()
{
    return reinterpret_cast<SonarController*>(sonarAdress);
}