#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/ColorRGBA.h>

//define sonar signal ports for easy configuration
#define siren0    2

#define ledR      9
#define ledG      10
#define ledB      11

//function definition
float get_measure_from(int digitalport);

void siren_message(const std_msgs::Bool& msg)
{
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(siren0, LOW);
  
  if(msg.data) {
    digitalWrite(siren0, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}

void led_message(const std_msgs::ColorRGBA& msg)
{
  analogWrite(ledR, msg.r);
  analogWrite(ledG, msg.g);
  analogWrite(ledB, msg.b);
}

//declare ros nodehandler, message and publisher
ros::NodeHandle nh;
ros::Subscriber<std_msgs::Bool> siren("siren", &siren_message);
ros::Subscriber<std_msgs::ColorRGBA> ledstrip("led", &led_message);

void setup()
{
  pinMode(siren0, OUTPUT);
  
  //init ros node and advertise the publisher
  nh.initNode();
  nh.subscribe(siren);
  nh.subscribe(ledstrip);
}

void loop()
{
  nh.spinOnce();
  delay(50);
}

