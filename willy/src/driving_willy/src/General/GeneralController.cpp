#include "../include.h"

using namespace std;
void *light;

GeneralController::GeneralController(ros::NodeHandle *nh, LightController *lightController)
{
    light = static_cast<void *>(lightController);
}

LightController *GeneralController::GetLightController()
{
    return static_cast<LightController *>(light);
}
