#include "../include.h"
#include <opencv2/highgui.hpp>

KinectController::KinectController()
{
}

void KinectController::Start()
{
    std::cout << "Oh hai there!" << std::endl;

    // ros::Subscriber sub = nh.subscribe("camera/rgb/image_raw", MY_ROS_QUEUE_SIZE, imgcb);
    //ros::Subscriber sub = nh->subscribe("camera/rgb/image_color", MY_ROS_QUEUE_SIZE, imgcb);

    cv::namedWindow("DrivingWilly");
    ros::spin();
    cv::destroyWindow("DrivingWilly");

    std::cout << "byebye my friend" << std::endl;
}

void KinectController::KinectCallback(const sensor_msgs::Image::ConstPtr &msg)
{
    std::cout << "Hey, listen!" << std::endl;
    try
    {
        cv_bridge::CvImageConstPtr cv_ptr;
        cv_ptr = cv_bridge::toCvShare(msg);

        cv::imshow("DrivingWilly", cv_ptr->image);
        cv::waitKey(1); // Update screen
    }
    catch (const cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}
