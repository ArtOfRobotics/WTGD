#!/bin/bash
# file: roscore.sh

source /opt/ros/kinetic/setup.bash
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:/Documents/WTGD

roscore
