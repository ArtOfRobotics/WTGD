#include "include.h"

using namespace std;

//Set the controller as a global variable.

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

    GPSController * gpsController = new GPSController();
    JoystickController * joystickController = new JoystickController();
    KeyboardController * keyboardController = new KeyboardController();

    KinectController * kinectController = new KinectController();
    LidarController * lidarController = new LidarController();
    SonarController * sonarController = new SonarController();

    LightController * lightController = new LightController();

    //Set up the subscriber for the GPS
    ros::Subscriber gpsSubscriber = n.subscribe("/gps", 200, &GPSController::GpsCallback, gpsController);

    //Set up the subscriber for the Joystick
    ros::Subscriber joystickSubscriber = n.subscribe("/joy", 10, &JoystickController::JoystickCallback, joystickController);

    //Set up the subscriber for the keyboard
    ros::Subscriber keyboardSubscriber = n.subscribe("/keyboard", 100, &KeyboardController::KeyboardCallback, keyboardController);

    //Set up the subscriber for the kinect
    ros::Subscriber kinectSubscriber = n.subscribe("/camera/depth_registered/image", 100, &KinectController::KinectCallback, kinectController);

    //Set up the subscriber for the lidar
    ros::Subscriber lidarSubscriber = n.subscribe("/scan", 100, &LidarController::LidarCallback, lidarController);

    //Set up the subscriber for the sonar
    ros::Subscriber subSonar = n.subscribe("/sonar", 100, &SonarController::SonarCallback, sonarController);

    //Set the asynchronised spinner for ros.
    ros::AsyncSpinner spinner(4);
    spinner.start();

    AutonomousDrivingController autonomousDrivingController = AutonomousDrivingController(&n, gpsController, joystickController, keyboardController, kinectController, lidarController, sonarController, lightController);
    autonomousDrivingController.Start();
    //JoyController joyController = JoyController(&willyController, argc, argv);
    //joyController.Start();

    // Wait
    ros::waitForShutdown();

    return 0;
}
