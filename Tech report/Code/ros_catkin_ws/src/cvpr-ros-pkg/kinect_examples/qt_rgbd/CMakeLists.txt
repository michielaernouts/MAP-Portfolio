cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)



# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

rosbuild_include(cuda cuda)

find_package(Qt4 REQUIRED)

INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/src )
ADD_DEFINITIONS(-D__STDC_CONSTANT_MACROS)

SET( MOC_HEADERS
src/SegmentMain.h 
src/SegmentView.h
)

SET(UI_FILES
)

SET(CUDA_SOURCES
src/invert.cu
)

MESSAGE(STATUS "MOC_HEADERS = ${MOC_HEADERS}")
QT4_WRAP_CPP(MOC_SOURCES ${MOC_HEADERS})
MESSAGE(STATUS "MOC_SOURCES = ${MOC_SOURCES}")


MESSAGE(STATUS "UI_FILES = ${UI_FILES}")
QT4_WRAP_UI(UI_HEADERS ${UI_FILES})
MESSAGE(STATUS "UI_HEADERS = ${UI_HEADERS}")

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
#CUDA_ADD_LIBRARY(invert src/invert.cu)

rosbuild_add_executable(
${PROJECT_NAME}
src/main.cpp
src/SegmentMain.cpp
src/SegmentView.cpp
${MOC_SOURCES}
${UI_HEADERS})
target_link_libraries(${PROJECT_NAME}  QtGui QtCore  cudaobjects)
CUDA_ADD_LIBRARY(cudaobjects ${CUDA_SOURCES} OPTIONS --ptxas-options=-v -DUNIX -D_DEBUG)

target_link_libraries(${PROJECT_NAME} cudaobjects shrutil_x86_64 cutil_x86_64)

