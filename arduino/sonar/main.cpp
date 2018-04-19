#include <ros.h>
#include <sensor_msgs/LaserEcho.h>

//define sonar signal ports for easy configuration
#define sonar0    3
#define sonar1    4
#define sonar2    5
#define sonar3    6
#define sonar4    7
#define sonar5    8
#define sonar6    9   //front under left
#define sonar7    10  //front under right

#define sonar8    11
#define sonar9    12
#define sonar10   13
#define sonar11   A0
#define sonar12   A1
#define sonar13   A2
#define sonar14   A3  //back under left
#define sonar15   A4  //back under right

/*
                front
      0 -- 1 - 2 -- 3 - 4 -- 5
      |                      |
      |    6           7     | 
      |                      | 
      |                      | 
      |      \       /       |
      |        under         |
      |      /       \       |
      |                      |
      |                      |
      |    14          15    |
      |                      |
      8 - 9 - 10 - 11 - 12 - 13
                back
*/

//function definition
float get_measure_from(int digitalport);

//declare ros nodehandler, message and publisher
ros::NodeHandle nh;
sensor_msgs::LaserEcho message;
ros::Publisher sonar("sonar", &message);

void setup()
{
  pinMode(sonar0, OUTPUT);
  pinMode(sonar1, OUTPUT);
  pinMode(sonar2, OUTPUT);
  pinMode(sonar3, OUTPUT);
  pinMode(sonar4, OUTPUT);
  pinMode(sonar5, OUTPUT);
  pinMode(sonar6, OUTPUT);
  pinMode(sonar7, OUTPUT);
  pinMode(sonar8, OUTPUT);
  pinMode(sonar9, OUTPUT);
  pinMode(sonar10, OUTPUT);
  pinMode(sonar11, OUTPUT);
  pinMode(sonar12, OUTPUT);
  pinMode(sonar13, OUTPUT);
  pinMode(sonar14, OUTPUT);
  pinMode(sonar15, OUTPUT);
  //init ros node and advertise the publisher
  nh.initNode();
  nh.advertise(sonar);
}

void loop()
{
  //get sonar values, we read the sonar in the following way
  //so there wont be any overlap in ultrasonic bursts
 
  float distance0 = get_measure_from(sonar0);
  float distance2 = get_measure_from(sonar2);
  float distance4 = get_measure_from(sonar4);
  float distance6 = get_measure_from(sonar6);
  float distance8 = get_measure_from(sonar8);
  float distance10 = get_measure_from(sonar10);
  float distance12 = get_measure_from(sonar12);
  float distance14 = get_measure_from(sonar14);

  delay(10);

  float distance1 = get_measure_from(sonar1);
  float distance3 = get_measure_from(sonar3);
  float distance5 = get_measure_from(sonar5);
  float distance7 = get_measure_from(sonar7);
  float distance9 = get_measure_from(sonar9);
  float distance11 = get_measure_from(sonar11);
  float distance13 = get_measure_from(sonar13);
  float distance15 = get_measure_from(sonar15);

  //add sonar values to message object and publish message
  float ech[] = {distance0 ,distance1, distance2,
                 distance3, distance4, distance5,
                 distance6, distance7, distance8,
                 distance9, distance10, distance11,
                 distance12, distance13, distance14,
                 distance15};
  message.echoes = ech;
  message.echoes_length = 16;
  sonar.publish(&message);

  nh.spinOnce();

  delay(100);
}

//return the measured distance of a connected Parallax Ping Ultrasonic Sensor in centimetres
float get_measure_from(int digitalport)
{
  //set pin as output so we can send a pulse
  pinMode(digitalport, OUTPUT);

  //set output to LOW before sending pulse
  digitalWrite(digitalport, LOW);
  delayMicroseconds(5);

  //send a 5uS pulse out to activate the sensor
  digitalWrite(digitalport, HIGH);
  delayMicroseconds(10);
  digitalWrite(digitalport, LOW);

  //change the digital pin to input to read the incoming pulse
  pinMode(digitalport, INPUT);

  //measure the length of the incoming pulse
  unsigned long pulseduration = pulseIn(digitalport, HIGH);

  //divide the pulse length by half
  pulseduration = pulseduration / 2;

  //convert to centimetres and return the value
  return float(pulseduration / 29);
}
