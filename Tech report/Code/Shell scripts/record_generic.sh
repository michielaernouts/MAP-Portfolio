#!/bin/bash

rosbag record --chunksize=1024 -b 512 --split --duration=7 -O rgb_bag /tf /erlecopter/front/image_front_raw /erlecopter/front/camera_front_info

