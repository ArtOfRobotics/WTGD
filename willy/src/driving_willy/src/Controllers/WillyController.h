#ifndef _WILLY_CONTROLLER_H_
#define _WILLY_CONTROLLER_H_

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

class WillyController
{
  public:
	//Constructor
	WillyController();

	//get en set  fuctions for Latitude and Longitude
	double getLng();
	double getLat();
	int getSat();
	void setLng(double lng);
	void setLat(double lat);
	void setSat(int sat);
	//Method which executes the given command.
	void Execute(ICommand &);

	//Method which handles the given sonar feedback.
	void SonarCallback(const sensor_msgs::LaserEcho &sonar);

	void KinectCallback(const sensor_msgs::Image::ConstPtr &msg);

	void GpsCallback(const std_msgs::String::ConstPtr &msg);

	//Method which calculates the distances.
	//int ReadDepthData(unsigned int height_pos, unsigned int width_pos, sensor_msgs::ImageConstPtr depth_image);

	//Method which calculates the distances by an array.
	//int ReadDepthDataArray(sensor_msgs::ImageConstPtr depth_image);

	//Method where the ROS Node can be given.
	void SetNode(ros::NodeHandle *n);

	//Method where a command can be given to the cmd_vel
	void SendCommandToArduino(geometry_msgs::Twist msg);

	//Method which returns the _ticks property
	geometry_msgs::Vector3 GetLatestTicks();

	//Method for returning the value by the degrees
	//int GetSonarValueByDegrees(int Degrees);

	//Calculating
	void CalculateMovingPossibilities();

	//Checks if the Controller received feedback from the Encoders.
	//Will be default false, after first WheelCallback true.
	bool ReceivedFirstTick;

	//Depth mm in front of the robot.
	int DepthInFront;

	//Sensor counters
	int ForwardSensorCount;
	int BackwardSensorCount;
	int LeftSensorCount;
	int RightSensorCount;

	//Property which stores if he can drive forward
	bool CanDriveForward;
	bool CanDriveBackward;
	bool CanTurnLeft;
	bool CanTurnRight;
	bool MovementKnown;

	//Array where the pointers in the array are where he reads the depth
	int ReadPointsInImage[10][2];

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

  private:
	//Latitude and longitude
	float lat, lng;
	//property which contains latest ticks of the encoder on willy.
	geometry_msgs::Vector3 _ticks;

	//The publisher where commands can be given throught cmd_vel
	ros::Publisher _commandPublisher;
	//ros::Publisher _movingPossibilitiesPublisher;
};

#endif
