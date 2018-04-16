#ifndef _SONAR_CONTROLLER_H_
#define _SONAR_CONTROLLER_H_

struct Sonar
{
    int Degrees;
    int Value;
};

struct SonarCheck
{
    int SonarID;
    int Value;
};

class SonarController
{
  public:
    SonarController();
    void SonarCallback(const sensor_msgs::LaserEcho &sonar);
    void CalculateMovingPossibilities();
    //Property which stores if he can drive forward
    bool CanDriveForward;
    bool CanDriveBackward;
    bool CanTurnLeft;
    bool CanTurnRight;
    bool MovementKnown;
    pugi::xml_document doc;
    pugi::xml_parse_result;
    pugi::xml_node tools;
    pugi::xml_node tool;
    pugi::xml_attribute attr;

  private:
    //Sensor counters
    int ForwardSensorCount;
    int BackwardSensorCount;
    int LeftSensorCount;
    int RightSensorCount;

    //Array with data of sonars.
    Sonar SonarData[10];

    int ChecksTurnLeftElements;
    SonarCheck ChecksTurnLeft[10];

    int ChecksTurnRightElements;
    SonarCheck ChecksTurnRight[10];

    int ChecksDriveForwardElements;
    SonarCheck ChecksDriveForward[10];

    int ChecksDriveBackwardElements;
    SonarCheck ChecksDriveBackward[10];
};

#endif