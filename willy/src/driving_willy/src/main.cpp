#include "include.h"

using namespace std;

//Set the controller as a global variable.

GPSController gpsController;
SonarController sonarController;
KinectController kinectController;
LidarController lidarController;

int main(int argc, char **argv)
{
    //Ros initation.
    ros::init(argc, argv, "DrivingWilly");
    ros::NodeHandle n;

    //placeholder values for gps route.
    std::vector<double> gpsLat;
    std::vector<double> gpsLong;
    gpsLat.push_back(12.4235);
    gpsLat.push_back(13.2355);
    n.setParam("gpsLat", gpsLat);
    gpsLong.push_back(10.4235);
    gpsLong.push_back(11.2355);
    n.setParam("gpsLong", gpsLong);

    //Set up the subscriber for the GPS
    ros::Subscriber gpsSubscriber = n.subscribe("/gps", 200, &GPSController::GpsCallback, &gpsController);

    //Set up the subscriber for the sonar
    ros::Subscriber subSonar = n.subscribe("/sonar", 100, &SonarController::SonarCallback, &sonarController);

    //Set up the subscriber for the kinect
    ros::Subscriber kinectSubscriber = n.subscribe("/camera/rgb/image_color", 100, &KinectController::KinectCallback, &kinectController);

    //Set up the subscriber for the lidar
    ros::Subscriber lidarSubscriber = n.subscribe("/scan", 100, &LidarController::LidarCallback, &lidarController);


    //Set the asynchronised spinner for ros.
    ros::AsyncSpinner spinner(4);
    spinner.start();

    AutonomousDrivingController autonomouseDriving = AutonomousDrivingController(&n);

    //Gives the node to the controller.
    autonomouseDriving.SetNode(&n);

    autonomouseDriving.Start();
    //JoyController joyController = JoyController(&willyController, argc, argv);
    //joyController.Start();

    // Wait
    ros::waitForShutdown();
    return 0;
}
