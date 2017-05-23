#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash

#### LAUNCH LSD SLAM
gnome-terminal --tab -e ~/scripts/SLAM/LSDSLAM/open_lsd_slam_viewer.sh --tab -e ~/scripts/SLAM/LSDSLAM/run_lsd_slam.sh

sleep 2
#### PLAY THE ROSBAG
gnome-terminal -e ~/scripts/play_bagfile.sh

