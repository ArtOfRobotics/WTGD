#include <ros.h>                                                      // include Ros Librarie
#include <geometry_msgs/Twist.h>                                      // include Ros Message type
#include <geometry_msgs/Vector3.h>                                    //
#include <std_msgs/String.h>

ros::NodeHandle nh;

int irun;                                    
int iturn;
unsigned char data[255];

void messageCb( const geometry_msgs::Twist& twistMsg)                 // subscriber setup
{                                                                     //
  irun = twistMsg.linear.x * 100;                                     //
  iturn = twistMsg.angular.z * 100;                                   //
}                                                                     //
                                                                      //
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &messageCb);    // subscriber setup

void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  
  Serial1.begin(19200, SERIAL_8E1);  
}
    
void loop()
{
    int drive = irun;                                                       //Set value from ros to motorcontroller
    int turn = iturn;                                                       //Set value from ros to motorcontroller

    if(drive > 100) {
      drive = 100;
    }
    
    if(drive < -100) {
      drive = -100;
    }
  
    if(turn > 100) {
      turn = 100;
    }
    if(turn < -100) {
      turn = -100;
    }

    data[0]=0x6A;                                              //-Datagram always start with 0x6A
    data[1]=drive;                                             //-Drive +-100
    data[2]=turn;                                              //-Turn +-100
    data[3]=0;                                                 //-Driv mode
    data[4]=0x0c;                                              //-Drive mode: 0x0c=fastest
    data[5]=0xff-(data[0]+data[1]+data[2]+data[3]+data[4]);    //-Checksum

    for(unsigned char i=0;i<6;i++)
    {
      Serial1.write(data[i]);                                  // Writing the data to the motorcontroller
    }
  
    nh.spinOnce();

    delay(20);
  
}

