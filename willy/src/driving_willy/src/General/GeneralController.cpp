#include "../include.h"

using namespace std;
void *light;
void *led;

static ros::Publisher sirenPublisher;
static ros::Publisher ledPublisher;

GeneralController::GeneralController(ros::NodeHandle *nh, LightController *lightController, LedController *ledController)
{
    light = static_cast<void *>(lightController);
    led = static_cast<void *>(ledController);
	sirenPublisher = nh->advertise<std_msgs::Bool>("/siren", 100);
    ledPublisher = nh->advertise<std_msgs::ColorRGBA>("/led", 100);
}

ros::Publisher GeneralController::GetSirenPublisher()
{
	return sirenPublisher;
}

ros::Publisher GeneralController::GetLedPublisher()
{
	return ledPublisher;
}

LightController *GeneralController::GetLightController()
{
    return static_cast<LightController *>(light);
}

LedController *GeneralController::GetLedController()
{
    return static_cast<LedController *>(led);
}
