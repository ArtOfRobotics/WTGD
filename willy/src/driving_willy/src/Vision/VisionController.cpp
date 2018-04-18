#include "../include.h"

using namespace std;
void *kinect;
void *lidar;
void *sonar;

VisionController::VisionController(ros::NodeHandle *nh, KinectController *kinectController, LidarController *lidarController, SonarController *sonarController)
{
    kinect = static_cast<void *>(kinectController);
    lidar = static_cast<void *>(lidarController);
    sonar = static_cast<void *>(sonarController);

    nh->getParam("min_y", min_y_);
    nh->getParam("max_y", max_y_);
    nh->getParam("min_x", min_x_);
    nh->getParam("max_x", max_x_);
    nh->getParam("max_z", max_z_);
    nh->getParam("goal_z", goal_z_);
    nh->getParam("z_scale", z_scale_);
    nh->getParam("x_scale", x_scale_);
    nh->getParam("enabled", enabled_);

    markerpub_ = nh->advertise<visualization_msgs::Marker>("marker", 1);
    bboxpub_ = nh->advertise<visualization_msgs::Marker>("bbox", 1);
    sub_ = nh->subscribe<sensor_msgs::Image>("camera/depth_registered/image_rect", 1, &KinectController::imagecb, kinectController);
}

KinectController *VisionController::GetKinectController()
{
    return static_cast<KinectController *>(kinect);
}

LidarController *VisionController::GetLidarController()
{
    return static_cast<LidarController *>(lidar);
}

SonarController *VisionController::GetSonarController()
{
    return static_cast<SonarController *>(sonar);
}