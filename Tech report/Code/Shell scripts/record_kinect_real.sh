#!/bin/bash

rosbag record -b 2048 /tf /camera/rgb/image_raw /camera/rgb/camera_info /camera/depth/image_raw /camera/depth/camera_info  
