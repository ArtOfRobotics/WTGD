#ifndef _KINECT_CONTROLLER_H_
#define _KINECT_CONTROLLER_H_s

class KinectController
{
public:
  //Constructor
  KinectController();
  void KinectCallback(const sensor_msgs::Image::ConstPtr &msg);
  void Start();

private:
  static const uint32_t MY_ROS_QUEUE_SIZE = 1000;
};

#endif