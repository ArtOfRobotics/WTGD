#include "include.h"

#include "Includes/PUGIXML/pugixml.hpp"
#include "Includes/PUGIXML/pugixml.cpp"
#include "Includes/PUGIXML/pugiconfig.hpp"
#define Node pugi::xml_node &
#define TreeWalker pugi::xml_tree_walker

//Set the controller as a global variable.
WillyController controller;

int main(int argc, char **argv)
{

    pugi::xml_document ConfigFile;
    ConfigFile.load_file("/home/willy/Documents/driving-willy/WTGD/willy/src/driving_willy/src/tree.xml");

    ConfigIterator walker;
    ConfigFile.traverse(walker);

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
    ros::Subscriber gpsSubscriber = n.subscribe("/gps", 200, &WillyController::GpsCallback, &controller);

    //Set up the subscriber for the sonar
    ros::Subscriber subSonar = n.subscribe("/sonar", 100, &WillyController::SonarCallback, &controller);
    //Gives the node to the controller.
    controller.SetNode(&n);

    //Set the asynchronised spinner for ros.
    ros::AsyncSpinner spinner(4);
    spinner.start();

    AutonomousDrivingController autonomouseDriving = AutonomousDrivingController(&controller, &n);
    autonomouseDriving.Start();
    //JoyController joyController = JoyController(&controller, argc, argv);
    //joyController.Start();
    KinectController kinectController = KinectController(&controller, argc, argv);
    kinectController.Start();

    // Wait
    ros::waitForShutdown();
    return 0;
}
