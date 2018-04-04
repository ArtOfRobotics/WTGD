#include "include.h"

//Set the controller as a global variable.
WillyController willyController;
KinectController kinectController;

int main(int argc, char **argv)
{
    //Ros initation.
    ros::init(argc, argv, "DrivingWilly");
    ros::NodeHandle n;
    //Transform odometryController = Transform(&n);
    //placeholder values for gps route.
    std::vector<double> gpsLat;
    std::vector<double> gpsLong;
    gpsLat.push_back(12.4235);
    gpsLat.push_back(13.2355);
    n.setParam("gpsLat", gpsLat);
    gpsLong.push_back(10.4235);
    gpsLong.push_back(11.2355);
    n.setParam("gpsLong", gpsLong);

    //Set up the subsriber of the wheel encoders to the WheelCallback of the WillyController.
    //ros::Subscriber subWheelEncoderWillyController = n.subscribe("/wheel_encoder", 200, &Transform::WheelCallback, &odometryController);

    //Set up the subscriber for the GPS
    ros::Subscriber gpsSubscriber = n.subscribe("/gps", 200, &WillyController::GpsCallback, &willyController);

    //Set up the subscriber for the sonar
    ros::Subscriber subSonar = n.subscribe("/sonar", 100, &WillyController::SonarCallback, &willyController);

    ros::Subscriber kinectSubscriber = n.subscribe("/camera/rgb/image_color", 100, &KinectController::KinectCallback, &kinectController);
    
    //Gives the node to the controller.
    willyController.SetNode(&n);

    //Set the asynchronised spinner for ros.
    ros::AsyncSpinner spinner(4);
    spinner.start();

    //AutonomousDrivingController autonomouseDriving = AutonomousDrivingController(&willyController, &n);
    //autonomouseDriving.Start();
    //JoyController joyController = JoyController(&willyController, argc, argv);
    //joyController.Start();
    KinectController kinectController = KinectController();
    kinectController.Start();

    // Wait
    ros::waitForShutdown();
    return 0;
}
