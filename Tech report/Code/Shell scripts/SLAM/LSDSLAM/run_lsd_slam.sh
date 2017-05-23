#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash

### GENERIC CAMERA SIMULATION
#rosrun lsd_slam_core live_slam /image:=/erlecopter/front/image_front_raw /camera_info:=/erlecopter/front/camera_front_info

### KINECT
#rosrun lsd_slam_core live_slam /image:=/camera/rgb/image_raw /camera_info:=/camera/rgb/camera_info

### WEBCAM (GSCAM)
##rosrun lsd_slam_core live_slam /image:=/camera/image /camera_info:=/camera/camera_info _calib:=webcam_calib.cfg

### WIDECAM (GSCAM)
rosrun lsd_slam_core live_slam /image:=/camera/image /camera_info:=/camera/camera_info _calib:=widecam_calib.cfg
