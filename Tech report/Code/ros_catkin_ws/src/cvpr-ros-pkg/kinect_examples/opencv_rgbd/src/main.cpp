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

//#include "invert.cuh"

using namespace std;


sensor_msgs::CameraInfo::ConstPtr cameraColorInfo_;
sensor_msgs::CameraInfo::ConstPtr cameraDepthInfo_;
cv_bridge::CvImagePtr cv_ptr;
cv::Mat debugImage_;


inline cv::Point3f to3D(cv::Point a) {
	cv::Point3f pt;
	float constant = 1.00 / cameraDepthInfo_->K[0];
	pt.x = (a.x - (cv_ptr->image.cols >> 1)) * cv_ptr->image.at<float> (a)
			* constant;
	pt.y = (a.y - (cv_ptr->image.rows >> 1)) * cv_ptr->image.at<float> (a)
			* constant;

	pt.z = cv_ptr->image.at<float> (a);
	return pt;
}

inline cv::Point to2D(cv::Point3f pt) {
	cv::Point a;
	a.x = pt.x/ pt.z * cameraDepthInfo_->K[0] +  (cv_ptr->image.cols >> 1);
	a.y = pt.y/ pt.z * cameraDepthInfo_->K[0] +  (cv_ptr->image.rows >> 1);
	return a;
}


void infoDepthCallback(const sensor_msgs::CameraInfo::ConstPtr& msg) {
	cameraDepthInfo_ = msg;
	cout << "received info" << endl;
}

void imageDepthCallback(const sensor_msgs::Image::ConstPtr& msg) {
	cout << "received depth image" << endl;
	ros::Time begin = ros::Time::now();
	if (!cameraDepthInfo_)
		return;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

//	debugImage_ = cv_ptr->image * 0.2;
	cvtColor(cv_ptr->image * 0.2, debugImage_, CV_GRAY2BGR);

//	float3 *field_g = 0;
//	size_t pitch = 0;
//	ros::Time start = ros::Time::now();
//	invert((float3*)debugImage_.data,(float3*)debugImage_.data,1.0f,debugImage_.cols,debugImage_.rows,&field_g,&pitch);
//	ros::Time stop = ros::Time::now();
//	cout <<"computation time: "<<(stop-start).toSec()<<"s"<<endl;

//	cuda_delete(field_g);
	cv::imshow("depth", debugImage_);
	cv::waitKey(3);

}

void imageColorCallback(const sensor_msgs::Image::ConstPtr& msg) {
	cout << "received color image" << endl;
	ros::Time begin = ros::Time::now();
	if (!cameraColorInfo_)
		return;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
	cv::cvtColor(cv_ptr->image,cv_ptr->image,CV_RGB2BGR);
	//cv::imwrite(fname+"-color.png",cv_ptr->image);

	cv::imshow("color", cv_ptr->image);
	cv::waitKey(3);

}

void infoColorCallback(const sensor_msgs::CameraInfo::ConstPtr& msg) {
	cameraColorInfo_ = msg;
	cout << "received info" << endl;
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "stub");

	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("camera/depth/image", 1, imageDepthCallback);
	ros::Subscriber sub2 = n.subscribe("camera/depth/camera_info", 1,infoDepthCallback);
	ros::Subscriber sub3 = n.subscribe("camera/rgb/image_color", 1, imageColorCallback);
	ros::Subscriber sub4 = n.subscribe("camera/rgb/camera_info", 1,	infoColorCallback);

	cv::namedWindow("depth");
	cv::namedWindow("color");

	ros::spin();
}
