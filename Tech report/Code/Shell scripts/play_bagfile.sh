#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash

# Play a rosbag
cd
read -p "Enter the rosbag that you want to use: " -i "$HOME/" -e path
echo $path

#### PLAY THE ROSBAG
rosbag play --clock $path
