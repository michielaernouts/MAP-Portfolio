#!/bin/bash
source ~/simulation/ros_catkin_ws/devel/setup.bash
mavproxy.py --master=127.0.0.1:14551 --out 10.0.0.8:7000
