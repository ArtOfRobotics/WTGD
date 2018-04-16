#include "../../include.h"

using namespace std;

LidarController::LidarController()
{
}

void LidarController::LidarCallback(const sensor_msgs::Image::ConstPtr &msg)
{
    std::cout << "Hey, listen!" << std::endl;
}