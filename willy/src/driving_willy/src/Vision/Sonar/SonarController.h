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

  private:
    //Sensor counters
    int ForwardSensorCount;
    int BackwardSensorCount;
    int LeftSensorCount;
    int RightSensorCount;

    //Array with data of sonars.
    Sonar SonarData[10];

    int ChecksTurnLeftElements;

    int ChecksTurnRightElements;

    int ChecksDriveForwardElements;

    int ChecksDriveBackwardElements;
};

#endif