#ifndef _MAIN_H_
#define _MAIN_H_

	//CPP Plugins //test
	#include <iostream>
	#include <queue>
	#include <string>
	//#include <unistd.h>
	#include <stdlib.h>
	#include <cmath>
	#include <list>
	//Movement includes & sensor messages
	#include <geometry_msgs/Vector3.h>
	#include <geometry_msgs/Twist.h>
	#include <std_msgs/String.h>
	// ROS includes
	#include <termios.h>
	#include <ros/ros.h>
	#include <sensor_msgs/PointCloud2.h>
	#include <std_msgs/Float64.h>
	#include <std_msgs/UInt8.h>
	#include <std_msgs/UInt8.h>
	#include <sensor_msgs/LaserEcho.h>
	#include <std_msgs/Int32MultiArray.h>
	//Projects scripts
	#include "Interfaces/ICommand.h"
	#include "Controllers/WillyController.h"
	#include "Controllers/JoyController.h"
	#include "Controllers/AutonomousDrivingController.h"
	//Commandos
	#include "Commands/Turn.h"
	#include "Commands/Forward.h"
	#include "Commands/Backward.h"
	#include "Commands/Stop.h"
	#include "Commands/Movement.h"
	#include "Commands/ForwardUntilHit.h"
	#include <fstream>
	//XML includes
	#include "Includes/PUGIXML/pugixml.hpp"
#endif
