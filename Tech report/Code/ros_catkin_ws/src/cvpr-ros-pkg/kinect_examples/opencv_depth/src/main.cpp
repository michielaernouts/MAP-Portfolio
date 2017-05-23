/*
 * detector.cpp
 *
 *  Created on: Mar 8, 2011
 *      Author: sturm
 */

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tf/transform_datatypes.h>
#include <iostream>
//#include <articulation_msgs/TrackMsg.h>

#include "invert.cuh"

using namespace std;


sensor_msgs::CameraInfo::ConstPtr cameraInfo_;
cv_bridge::CvImagePtr cv_ptr;
cv::Mat debugImage_;


inline cv::Point3f to3D(cv::Point a) {
	cv::Point3f pt;
	float constant = 1.00 / cameraInfo_->K[0];
	pt.x = (a.x - (cv_ptr->image.cols >> 1)) * cv_ptr->image.at<float> (a)
			* constant;
	pt.y = (a.y - (cv_ptr->image.rows >> 1)) * cv_ptr->image.at<float> (a)
			* constant;

	pt.z = cv_ptr->image.at<float> (a);
	return pt;
}

inline cv::Point to2D(cv::Point3f pt) {
	cv::Point a;
	a.x = pt.x/ pt.z * cameraInfo_->K[0] +  (cv_ptr->image.cols >> 1);
	a.y = pt.y/ pt.z * cameraInfo_->K[0] +  (cv_ptr->image.rows >> 1);
	return a;
}


void infoCallback(const sensor_msgs::CameraInfo::ConstPtr& msg) {
	cameraInfo_ = msg;
	cout << "received info" << endl;
}

void imageCallback(const sensor_msgs::Image::ConstPtr& msg) {
	cout << "received image" << endl;
	ros::Time begin = ros::Time::now();
	if (!cameraInfo_)
		return;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

//	debugImage_ = cv_ptr->image * 0.2;
	cvtColor(cv_ptr->image * 0.2, debugImage_, CV_GRAY2BGR);

	float3 *field_g = 0;
	size_t pitch = 0;
	invert((float3*)debugImage_.data,(float3*)debugImage_.data,1.0f,debugImage_.cols,debugImage_.rows,&field_g,&pitch);
	cuda_delete(field_g);
	cv::imshow("depth", debugImage_);
	cv::waitKey(3);

}


int main(int argc, char** argv) {
	ros::init(argc, argv, "stub");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("camera/depth/image", 1, imageCallback);
	ros::Subscriber sub2 = n.subscribe("camera/depth/camera_info", 1,
			infoCallback);

	cv::namedWindow("depth");

	ros::spin();
}
