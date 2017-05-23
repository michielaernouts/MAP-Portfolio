#!/bin/bash
rosbag record --chunksize=256 -b 2048 -O kinect_bag /erlecopter/ground_truth_odometry /tf /camera/rgb/image_color /camera/rgb/camera_info /camera/depth_registered/sw_registered/image_rect_raw /camera/depth/camera_info 

