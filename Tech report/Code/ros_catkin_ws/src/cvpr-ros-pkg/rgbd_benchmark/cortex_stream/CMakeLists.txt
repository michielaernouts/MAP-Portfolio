cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE Debug)

rosbuild_init()
set (CMAKE_C_COMPILER "/usr/bin/colorgcc")
set (CMAKE_CXX_COMPILER "/usr/bin/colorgcc")

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()
if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PLATFORM 64)
else()
    set(PLATFORM 32)
endif()

#common commands for building c++ executables and libraries
#rosbuild_add_library(cortex src/stream_node.cpp)
set(CORTEX_LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
message(STATUS "Adding link_directories: " ${CORTEX_LIB_DIR})
link_directories(${CORTEX_LIB_DIR})
rosbuild_add_executable(${PROJECT_NAME} src/cortex_stream.cpp)
if(PLATFORM EQUAL 32)
    MESSAGE(STATUS "Linking 32-bit library")
    target_link_libraries(${PROJECT_NAME} cortex_sdk)
elseif(PLATFORM EQUAL 64)
    MESSAGE(STATUS "Linking 64-bit library")
    target_link_libraries(${PROJECT_NAME} cortex_sdk_x64)
endif()

rosbuild_add_executable(cortex_fake_stream src/cortex_fake_stream.cpp)
#rosbuild_add_boost_directories()
rosbuild_link_boost(${PROJECT_NAME} thread)
#target_link_libraries(example ${PROJECT_NAME})
