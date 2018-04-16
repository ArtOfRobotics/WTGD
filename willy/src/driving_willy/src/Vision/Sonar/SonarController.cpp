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

    ChecksTurnLeft[10] = new SonarCheck[10];
    ChecksTurnRight[10] = new SonarCheck[10];
    ChecksDriveBackward[10] = new SonarCheck[10];
    ChecksDriveForward[10] = new SonarCheck[10];

    pugi::xml_document doc;
    pugi::xml_parse_result result;
    pugi::xml_node tools;
    pugi::xml_node tool;
    pugi::xml_attribute attr;

    //Load sonar array data from xml
    result = doc.load_file("src/driving_willy/src/tree.xml");
    if (result.status != 0)
    {
        printf("404 - Laden van bestand is mislukt\n");
    }

    //Loop through all XML nodes
    tools = doc.child("Willy").child("SonarChecks");

    for (tool = tools.first_child(); tool; tool = tool.next_sibling())
    {
        for (attr = tool.first_attribute(); attr; attr = attr.next_attribute())
        {
            if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "TurnLeft") == 0))
            {
                *ChecksTurnLeft[LeftSensorCount].SonarID = tool.attribute("SonarID").as_int();
                *ChecksTurnLeft[LeftSensorCount].Value = tool.attribute("Value").as_int();
                LeftSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "TurnRight") == 0))
            {
                //ChecksTurnRight[RightSensorCount].SonarID = tool.attribute("SonarID").as_int();
                //ChecksTurnRight[RightSensorCount].Value = tool.attribute("Value").as_int();
                RightSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "DriveForward") == 0))
            {
                //printf("Er is een element toegevoegd! SonarID: %d. Value: %d.", tool.attribute("SonarID").as_int(), tool.attribute("Value").as_int());
                //ChecksDriveForward[ForwardSensorCount].SonarID = tool.attribute("SonarID").as_int();
                //ChecksDriveForward[ForwardSensorCount].Value = tool.attribute("Value").as_int();
                ForwardSensorCount++;
            }
            else if ((strcmp(attr.name(), "type") == 0) && (strcmp(attr.value(), "DriveBackward") == 0))
            {
                //ChecksDriveBackward[BackwardSensorCount].SonarID = tool.attribute("SonarID").as_int();
                //ChecksDriveBackward[BackwardSensorCount].Value = tool.attribute("Value").as_int();
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
    CanDriveForward = true;
    CanDriveBackward = true;
    CanTurnLeft = true;
    CanTurnRight = true;

    printf("Calculate moving possibilities:\n");

    for (int i = 0; i < sizeof(ChecksDriveForward) / sizeof(ChecksDriveForward[0]); i++)
    {
        printf("Max value: %d Sensor value: %d\n", ChecksDriveForward[i].Value, SonarData[ChecksDriveForward[i].SonarID].Value);
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