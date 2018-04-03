#include "../include.h"
#include <iostream>
#include <sstream>

//Author: Henk-Jan Leusink
//Description: 	This class is the controller of Willy.
// 				It handles feedback which is send from Willy and send controls to Willy for driving.
//Default Constructor

WillyController::WillyController()
{
	ReceivedFirstTick = false;
	CanDriveForward = true;
	CanDriveBackward = true;
	CanTurnLeft = true;
	CanTurnRight = true;

	////
	//// |3-------2--------1|
	//// |                  |
	//// |                  |
	//// |4                0|
	//// |                  |
	//// |                  |
	//// |                  |
	//// |                  |
	//// |                  |
	//// |5                9|
	//// |                  |
	//// |                  |
	//// |6-------7--------8|
	////

	//Load sonar array data from xml
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("src/driving_willy/src/tree.xml");
	if (result.status != 0)
	{
		printf("404 - Laden van bestand is mislukt\n");
	}

	pugi::xml_node tools = doc.child("Willy").child("SonarChecks");

	for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
	{
		for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
		{
			std::cout << " " << attr.name() << "=" << attr.value();
			//attr.value()

			//printf("Attribuut naam: %c, Attribuut waarde: %c\n", attr.name(), attr.value());
			if (attr.name() == "type" && attr.value() == "TurnLeft")
			{
				printf("hoihoi");
				ChecksTurnLeft[((sizeof(ChecksTurnLeft) / sizeof(ChecksTurnLeft[0])) + 1)].SonarID = tool.attribute("SonarID").as_int();
				ChecksTurnLeft[((sizeof(ChecksTurnLeft) / sizeof(ChecksTurnLeft[0])) + 1)].Value = tool.attribute("Value").as_int();
			}
			else if (tool.attribute("type").value() == "TurnRight")
			{
				ChecksTurnRight[((sizeof(ChecksTurnRight) / sizeof(ChecksTurnRight[0])) + 1)].SonarID = tool.attribute("SonarID").as_int();
				ChecksTurnRight[((sizeof(ChecksTurnRight) / sizeof(ChecksTurnRight[0])) + 1)].Value = tool.attribute("Value").as_int();
			}
			else if (tool.attribute("type").value() == "DriveForward")
			{
				printf("Hoi ik ben vooruid aan het vullen");
				ChecksDriveForward[((sizeof(ChecksDriveForward) / sizeof(ChecksDriveForward[0])) + 1)].SonarID = tool.attribute("SonarID").as_int();
				ChecksDriveForward[((sizeof(ChecksDriveForward) / sizeof(ChecksDriveForward[0])) + 1)].Value = tool.attribute("Value").as_int();
			}
			else if (tool.attribute("type").value() == "DriveBackward")
			{
				ChecksDriveBackward[((sizeof(ChecksDriveBackward) / sizeof(ChecksDriveBackward[0])) + 1)].SonarID = tool.attribute("SonarID").as_int();
				ChecksDriveBackward[((sizeof(ChecksDriveBackward) / sizeof(ChecksDriveBackward[0])) + 1)].Value = tool.attribute("Value").as_int();
			}
		}

		std::cout << std::endl;
	}
}

//This method executes the command which extend the ICommand.
void WillyController::Execute(ICommand &command)
{
	command.Execute();
}

//This method gets fired wen there's a new message from the sonar system.
void WillyController::SonarCallback(const sensor_msgs::LaserEcho &sonar)
{
	for (int i = 0; i < 10; i++)
	{
		//printf("%d\n", SonarData[i].Value);

		SonarData[i].Value = sonar.echoes[i];
	}

	/*
	printf("\n");
	printf("|3: %d-------2: %d--------1: %d|\n", SonarData[3].Value, SonarData[2].Value, SonarData[1].Value);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|4: %d                    0: %d|\n", SonarData[4].Value, SonarData[0].Value);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|5: %d                    9: %d|\n", SonarData[5].Value, SonarData[9].Value);
	printf("|                              |\n");
	printf("|                              |\n");
	printf("|6: %d-------7: %d--------8: %d|\n", SonarData[6].Value, SonarData[7].Value, SonarData[8].Value);
	printf("\n");
	*/

	CalculateMovingPossibilities();
}

void WillyController::GpsCallback(const std_msgs::String::ConstPtr &msg)
{
	//printf("gps msg = %s\n", msg->data.c_str());
	std::string input = msg->data.c_str();
	std::istringstream ss(input);
	std::string token;
	int counter = 0;
	while (std::getline(ss, token, ','))
	{
		//printf("%s\n", (char *)token.c_str());
		++counter;
	}
	// msg->data.c_str().substr (0,5);
}

double WillyController::getLng()
{
}

double WillyController::getLat()
{
}

int WillyController::getSat()
{
}

void WillyController::setLng(double lng)
{
}

void WillyController::setLat(double lat)
{
}
void WillyController::setSat(int sat)
{
}

//This method receives the ROS NodeHandle and creates a new publisher
void WillyController::SetNode(ros::NodeHandle *n)
{
	_commandPublisher = n->advertise<geometry_msgs::Twist>("/cmd_vel", 100);
	//_movingPossibilitiesPublisher = n->advertise<std_msgs::Int32MultiArray>("/possible_directions", 100);
}

void WillyController::CalculateMovingPossibilities()
{
	CanDriveForward = true;
	CanDriveBackward = true;
	CanTurnLeft = true;
	CanTurnRight = true;

	for (int i = 0; i < sizeof(ChecksDriveForward) / sizeof(ChecksDriveForward[0]); i++)
	{
		printf("SonarID: %d --- Sonar waarde: %d\n", ChecksDriveForward[i].SonarID, ChecksDriveForward[i].Value);
		if (ChecksDriveForward[i].Value != 0 && SonarData[ChecksDriveForward[i].SonarID].Value < ChecksDriveForward[i].Value)
		{
			CanDriveForward = false;
			//printf("Sonar: %d, can't drive forward:%d < %d\n", ChecksDriveForward[i].SonarID, SonarData[ChecksDriveForward[i].SonarID].Value, ChecksDriveForward[i].Value);
			break;
		}
	}

	for (int i = 0; i < sizeof(ChecksTurnLeft) / sizeof(ChecksTurnLeft[0]); i++)
	{
		if (ChecksTurnLeft[i].Value != 0 && SonarData[ChecksTurnLeft[i].SonarID].Value < ChecksTurnLeft[i].Value)
		{
			CanTurnLeft = false;
			//MovementKnown = true;
			//printf("Sonar: %d, can't turn left:%d < %d\n", ChecksTurnLeft[i].SonarID, SonarData[ChecksTurnLeft[i].SonarID].Value, ChecksTurnLeft[i].Value);
			break;
		}
	}

	for (int i = 0; i < sizeof(ChecksTurnRight) / sizeof(ChecksTurnRight[0]); i++)
	{
		if (ChecksTurnRight[i].Value != 0 && SonarData[ChecksTurnRight[i].SonarID].Value < ChecksTurnRight[i].Value)
		{
			CanTurnRight = false;
			//MovementKnown = true;
			//printf("Sonar: %d, can't turn right:%d < %d\n", ChecksTurnRight[i].SonarID, SonarData[ChecksTurnRight[i].SonarID].Value, ChecksTurnRight[i].Value);
			break;
		}
	}

	for (int i = 0; i < sizeof(ChecksDriveBackward) / sizeof(ChecksDriveBackward[0]); i++)
	{
		if (ChecksDriveBackward[i].Value != 0 && SonarData[ChecksDriveBackward[i].SonarID].Value < ChecksDriveBackward[i].Value)
		{
			CanDriveBackward = false;
			//MovementKnown = true;
			//printf("Sonar: %d, can't drive backward:%d < %d\n", ChecksDriveBackward[i].SonarID, SonarData[ChecksDriveBackward[i].SonarID].Value, ChecksDriveBackward[i].Value);
			break;
		}
	}

	/*std_msgs::Int32MultiArray array;

	array.data.clear();
	array.data.push_back(CannotDrive);
	array.data.push_back(CanDriveForward);
	array.data.push_back(CanTurnLeft);
	array.data.push_back(CanDriveBackward);
	array.data.push_back(CanTurnRight);

	//Publish array
	_movingPossibilitiesPublisher.publish(array);
	//ROS_INFO("-----------------------------------------------");
	*/
}

//This method sends the msg to the arduino. It can be controlled from the commands.
void WillyController::SendCommandToArduino(geometry_msgs::Twist msg)
{
	_commandPublisher.publish(msg);
}

//This method returns the last feedback which is received by the arduino.
geometry_msgs::Vector3 WillyController::GetLatestTicks()
{
	return _ticks;
}
