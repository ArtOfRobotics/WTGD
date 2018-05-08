#include "../include.h"

using namespace std;
void *light;

static ros::Publisher sirenPublisher;

GeneralController::GeneralController(ros::NodeHandle *nh, LightController *lightController)
{
    light = static_cast<void *>(lightController);
	sirenPublisher = nh->advertise<std_msgs::Bool>("/siren", 100);
}

ros::Publisher GeneralController::GetSirenPublisher()
{
	return sirenPublisher;
}

LightController *GeneralController::GetLightController()
{
    return static_cast<LightController *>(light);
}
