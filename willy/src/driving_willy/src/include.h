#ifndef _MAIN_H_
#define _MAIN_H_

//CPP Plugins //test
#include <iostream>
#include <queue>
#include <string>

//#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>
#include <list>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

//Movement includes & sensor messages
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

// ROS includes
#include <termios.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt8.h>
#include <sensor_msgs/LaserEcho.h>
#include <std_msgs/Int32MultiArray.h>

//Vision controllers
#include "Vision/Kinect/KinectController.h"
#include "Vision/Lidar/LidarController.h"
#include "Vision/Sonar/SonarController.h"
#include "Vision/VisionController.h"

//Movement controllers
#include "Movement/GPS/GPSController.h"
#include "Movement/Joystick/JoystickController.h"
#include "Movement/MovementController.h"
#include "Movement/Keyboard/KeyboardController.h"

//Autonomous driving controller
#include "Controllers/AutonomousDrivingController.h"

//Commandos
#include <fstream>
#include <math.h>
#include <cmath>

//XML includes
#include "Includes/PUGIXML/pugixml.hpp"
#include "Includes/PUGIXML/pugiconfig.hpp"

//Kinect includes
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#endif
