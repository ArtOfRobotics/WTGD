#include "../../include.h"
#include <iostream>
#include <sstream>

using namespace std;

SonarController::SonarController()
{
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

    //Loop through all XML nodes
    pugi::xml_node tools = doc.child("Willy").child("SonarChecks");

    for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
    {
        for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
        {
            if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "TurnLeft") == 0))
            {
                ChecksTurnLeft[LeftSensorCount].SonarID = tool.attribute("SonarID").as_int();
                ChecksTurnLeft[LeftSensorCount].Value = tool.attribute("Value").as_int();
                LeftSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "TurnRight") == 0))
            {
                ChecksTurnRight[RightSensorCount].SonarID = tool.attribute("SonarID").as_int();
                ChecksTurnRight[RightSensorCount].Value = tool.attribute("Value").as_int();
                RightSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "DriveForward") == 0))
            {
                ChecksDriveForward[ForwardSensorCount].SonarID = tool.attribute("SonarID").as_int();
                ChecksDriveForward[ForwardSensorCount].Value = tool.attribute("Value").as_int();
                ForwardSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "DriveBackward") == 0))
            {
                ChecksDriveBackward[BackwardSensorCount].SonarID = tool.attribute("SonarID").as_int();
                ChecksDriveBackward[BackwardSensorCount].Value = tool.attribute("Value").as_int();
                BackwardSensorCount++;
            }
        }
    }
}

//This method gets fired wen there's a new message from the sonar system.
void SonarController::SonarCallback(const sensor_msgs::LaserEcho &sonar)
{
    for (int i = 0; i < 10; i++)
    {
        SonarData[i].Value = sonar.echoes[i];
    }
    CalculateMovingPossibilities();
}

void SonarController::CalculateMovingPossibilities()
{
    printf("Ik ben in de sonar controller");

    CanDriveForward = true;
    CanDriveBackward = true;
    CanTurnLeft = true;
    CanTurnRight = true;

    for (int i = 0; i < sizeof(ChecksDriveForward) / sizeof(ChecksDriveForward[0]); i++)
    {
        if (ChecksDriveForward[i].Value != 0 && SonarData[ChecksDriveForward[i].SonarID].Value < ChecksDriveForward[i].Value)
        {
            CanDriveForward = false;
            break;
        }
    }

    for (int i = 0; i < sizeof(ChecksTurnLeft) / sizeof(ChecksTurnLeft[0]); i++)
    {
        if (ChecksTurnLeft[i].Value != 0 && SonarData[ChecksTurnLeft[i].SonarID].Value < ChecksTurnLeft[i].Value)
        {
            CanTurnLeft = false;
            break;
        }
    }

    for (int i = 0; i < sizeof(ChecksTurnRight) / sizeof(ChecksTurnRight[0]); i++)
    {
        if (ChecksTurnRight[i].Value != 0 && SonarData[ChecksTurnRight[i].SonarID].Value < ChecksTurnRight[i].Value)
        {
            CanTurnRight = false;
            break;
        }
    }

    for (int i = 0; i < sizeof(ChecksDriveBackward) / sizeof(ChecksDriveBackward[0]); i++)
    {
        if (ChecksDriveBackward[i].Value != 0 && SonarData[ChecksDriveBackward[i].SonarID].Value < ChecksDriveBackward[i].Value)
        {
            CanDriveBackward = false;
            break;
        }
    }
}