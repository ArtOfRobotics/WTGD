#include "../include.h"

using namespace std;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    useKinect = false;
    useLidar = false;
    useSonar = false;

    //Call movement controllers if enabled
    if (useKinect)
    {
        *kinectController = KinectController();
    }

    if (useLidar)
    {
        *lidarController = LidarController();
    }

    if (useSonar)
    {
        *sonarController = SonarController();
    }
}