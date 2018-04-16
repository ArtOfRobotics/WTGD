#include "../../include.h"

using namespace std;

LidarController::LidarController()
{
    printf("Er is een nieuwe Lidar controller aangemaakt!\n");
}

void LidarController::LidarCallback(const sensor_msgs::LaserScan &msg)
{
    std::cout << "Hey, listen!" << std::endl;
}