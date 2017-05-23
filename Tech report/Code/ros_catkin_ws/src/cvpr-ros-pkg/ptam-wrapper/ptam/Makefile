#ROS_ROOT=/opt/ros/diamondback/ros
#ROS_PACKAGE_PATH=/opt/ros/diamondback/ros:${HOME}/ros
#TOON_DIR=$(shell ROS_ROOT=${ROS_ROOT} ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH} ${ROS_ROOT}/bin/rospack find toon)
#LIBCVD_DIR=$(shell ROS_ROOT=${ROS_ROOT} ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH} ${ROS_ROOT}/bin/rospack find libcvd)
#GVARS3_DIR=$(shell ROS_ROOT=${ROS_ROOT} ROS_PACKAGE_PATH=${ROS_PACKAGE_PATH} ${ROS_ROOT}/bin/rospack find gvars3)

TOON_DIR=$(shell rospack find toon)
LIBCVD_DIR=$(shell rospack find libcvd)
GVARS3_DIR=$(shell rospack find gvars3)

all: checkout configure_make_install
	cd build/PTAM && \
		EXTRA_CFLAGS="-I${TOON_DIR}/include -I${LIBCVD_DIR}/include -I${GVARS3_DIR}/include" \
		EXTRA_LFLAGS="-L${TOON_DIR}/lib -L${LIBCVD_DIR}/lib -L${GVARS3_DIR}/lib \
			-Wl,-rpath=${TOON_DIR}/lib -Wl,-rpath=${LIBCVD_DIR}/lib -Wl,-rpath=${GVARS3_DIR}/lib" \
		make

checkout: 
	mkdir build
	cd build && wget http://www.robots.ox.ac.uk/~gk/PTAM/PTAM.zip
	cd build && unzip PTAM.zip
	touch checkout

configure_make_install:
	cp build/PTAM/Build/Linux/* build/PTAM
	cd build/PTAM && patch < ../../patch
	cd build/PTAM && patch < ../../patch-videosource
	cp *.cc build/PTAM
	cd build/PTAM && \
		EXTRA_CFLAGS="-I${TOON_DIR}/include -I${LIBCVD_DIR}/include -I${GVARS3_DIR}/include" \
		EXTRA_LFLAGS="-L${TOON_DIR}/lib -L${LIBCVD_DIR}/lib -L${GVARS3_DIR}/lib \
			-Wl,-rpath=${TOON_DIR}/lib -Wl,-rpath=${LIBCVD_DIR}/lib -Wl,-rpath=${GVARS3_DIR}/lib" \
		make
	touch configure_make_install

.PHONY: clean

clean:
	rm -rf checkout configure_make_install build include bin lib

