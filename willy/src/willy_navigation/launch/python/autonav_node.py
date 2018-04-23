#!/usr/bin/env python
from __future__ import division
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge
import numpy as np
import random
import threading

class AutonavNode(object):

    def __init__(self):
        # CONSTANTS
        self.min_distance = 1500 #millimeters
        self.speed = 1
        self.avoiding = False
        # Initialize node
        rospy.init_node("autonav_node")
        self.cv_bridge = CvBridge()
        # Create subscriber for Kinect images
        self.sub = rospy.Subscriber("camera/depth_registered/image_raw", Image, self.process_depth_image)
        # Create publisher for movement commands
        self.pub = rospy.Publisher("cmd_vel", Twist, queue_size=1)
        # Allow MMM node to start
        rospy.sleep(1/20)
        # Start moving forward initially
    	vel_msg = Twist()
        vel_msg.linear.x = 0.4
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
        self.pub.publish(vel_msg)
        rospy.spin()

    def process_depth_image(self, msg):
        im = self.cv_bridge.imgmsg_to_cv2(msg)
	croppedLeft = im[0:380, 160:240]
	croppedRight = im[0:380, 240:320]

        min_pointLeft = croppedLeft[croppedLeft.nonzero()].min()
	min_pointRight = croppedRight[croppedRight.nonzero()].min()
        print(min_pointLeft)
	

        if min_pointLeft < self.min_distance:
            if not self.avoiding:
                threading.Thread(target=self.avoid_rightObstacle).start()
        else:
            self.avoiding = False

        if min_pointRight < self.min_distance:
            if not self.avoiding:
                threading.Thread(target=self.avoid_leftObstacle).start()
        else:
            self.avoiding = False

    def avoid_leftObstacle(self):
        print("LEFT AVOIDING")
        self.avoiding = True
	vel_msg = Twist()
        vel_msg.linear.x = -0.4
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
	self.pub.publish(vel_msg)
	rospy.sleep(1/10)	
	
	vel_msg = Twist()
        vel_msg.linear.x = 0
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0.4
        self.pub.publish(vel_msg)
        while self.avoiding:
            rospy.sleep(1/20)
        print("DONE LEFT AVOIDING")
	vel_msg = Twist()
        vel_msg.linear.x = 0.4
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
     	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
	self.pub.publish(vel_msg)

    def avoid_rightObstacle(self):
        print("RIGHT AVOIDING")
        self.avoiding = True
	vel_msg = Twist()
        vel_msg.linear.x = -0.4
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
	self.pub.publish(vel_msg)
	rospy.sleep(1/10)	

	vel_msg = Twist()
        vel_msg.linear.x = 0
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
    	vel_msg.angular.y = 0
    	vel_msg.angular.z = -0.4
        self.pub.publish(vel_msg)
        while self.avoiding:
            rospy.sleep(1/20)
        print("DONE RIGHT AVOIDING")
	vel_msg = Twist()
        vel_msg.linear.x = 0.4
    	vel_msg.linear.y = 0
    	vel_msg.linear.z = 0
    	vel_msg.angular.x = 0
     	vel_msg.angular.y = 0
    	vel_msg.angular.z = 0
	self.pub.publish(vel_msg)

if __name__ == '__main__':
    autonav_node = AutonavNode()
