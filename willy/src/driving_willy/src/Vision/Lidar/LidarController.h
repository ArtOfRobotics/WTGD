#ifndef _LIDAR_CONTROLLER_H_
#define _LIDAR_CONTROLLER_H_

class LidarController
{
  public:
    //Constructor
    LidarController();
    void LidarCallback(const sensor_msgs::LaserScan &msg);

  private:
};

#endif