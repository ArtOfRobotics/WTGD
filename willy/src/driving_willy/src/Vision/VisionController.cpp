#include "../include.h"

using namespace std;

VisionController::VisionController()
{
    useKinect = false;
    useLidar = false;
    useSonar = false;

    //Call movement controllers if enabled
    if (useKinect)
    {
        KinectController kinectController = KinectController();
    }

    if (useLidar)
    {
        LidarController lidarController = LidarController();
    }

    if (useSonar)
    {
        SonarController sonarController = SonarController();
    }
}

KinectController *VisionController::GetKinectController()
{
    return &kinectController;
}

LidarController *VisionController::GetLidarController()
{
    return &lidarController;
}

SonarController *VisionController::GetSonarController()
{
    return &joystickController;
}
