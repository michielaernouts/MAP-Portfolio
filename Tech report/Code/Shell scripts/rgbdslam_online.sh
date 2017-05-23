#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash

sleep 2

## Set Erle-Brain as ROS Master
echo "Setting ROS MASTER to 10.0.0.1:11311"
export ROS_MASTER_URI=http://10.0.0.1:11311
export ROS_IP=0.0.0.0

roslaunch rgbdslam demo_rgbdslam.launch
