#include "../../include.h"
//#include <opencv2/highgui.hpp>

using namespace std;

KinectController::KinectController()
{
    printf("Er is een nieuwe Kinect controller aangemaakt!\n");
}

void KinectController::KinectCallback(const sensor_msgs::Image::ConstPtr &depth_msg)
{

}
