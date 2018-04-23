#!/usr/bin/env python
from __future__ import division
import rospy
from geometry_msgs.msg import Twist

class AutonavNode(object):

    def __init__(self):
        # Initialize node
        rospy.init_node("autonav_node1")
        # Create publisher for movement commands
        self.pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)
	rospy.sleep(1)    	
	vel_msg = Twist()
        vel_msg.linear.x = 0
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
        self.pub.publish(vel_msg) 
        rospy.spin()

if __name__ == '__main__':
    autonav_node = AutonavNode()
