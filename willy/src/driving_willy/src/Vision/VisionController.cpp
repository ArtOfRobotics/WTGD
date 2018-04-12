#include "../include.h"

using namespace std;
void *kinectAdress;
void *lidarAdress;
void *sonarAdress;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = true;

    //Call movement controllers if enabled
    if (useKinect)
    {
        kinectAdress = (int)kinectController;
    }

    if (useLidar)
    {
        lidarAdress = (int)lidarController;
    }

    if (useSonar)
    {
        sonarAdress = (int)sonarController;
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