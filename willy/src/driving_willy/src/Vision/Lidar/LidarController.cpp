#include "../../include.h"

LidarController::LidarController()
{
}

void LidarController::LidarCallback(const sensor_msgs::Image::ConstPtr &msg)
{
    std::cout << "Hey, listen!" << std::endl;
    try
    {
        cv_bridge::CvImageConstPtr cv_ptr;
        cv_ptr = cv_bridge::toCvShare(msg);

        //cv::imshow("DrivingWilly", cv_ptr->image);
        //cv::waitKey(1); // Update screen
    }
    catch (const cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}