#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash

### LAUNCH GAZEBO
gnome-terminal -e ~/scripts/gazebo_simulation.sh


#### LAUNCH LSD SLAM
sleep 5
gnome-terminal --tab -e ~/scripts/SLAM/LSDSLAM/open_lsd_slam_viewer.sh --tab -e ~/scripts/SLAM/LSDSLAM/run_lsd_slam.sh

