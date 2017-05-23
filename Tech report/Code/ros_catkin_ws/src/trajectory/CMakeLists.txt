cmake_minimum_required(VERSION 2.8.3)
project(trajectory)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(erle_world src/erle_world.cpp)
target_link_libraries(erle_world  ${catkin_LIBRARIES})
add_dependencies(erle_world  erle_world_generate_messages_cpp)

add_executable(vbuilding src/vbuilding.cpp)
target_link_libraries(vbuilding  ${catkin_LIBRARIES})
add_dependencies(vbuilding  vbuilding_generate_messages_cpp)
