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
#include <string>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

cv::Mat rgbLatestImage;
cv::Mat depthLatestImage;

void saveImage() {
	static int frame = 0;

	cv::Mat depth16bitImage;
	depthLatestImage.convertTo(depth16bitImage, CV_16UC1, 5000, 0);

	cerr << "saving image number "<<frame << endl;
	cv::imwrite(str(format("%05d-d.png")%frame), depth16bitImage);
	cv::imwrite(str(format("%05d-rgb.png")%frame), rgbLatestImage);
	frame++;
}

void mouseHandler(int event, int x, int y, int flags, void *param) {
	switch (event) {
	/* left button down */
	case CV_EVENT_LBUTTONDOWN:
		saveImage();
		break;

		/* right button down */
	case CV_EVENT_RBUTTONDOWN:
		fprintf(stdout, "Right Button Down.	");
		break;

		/* mouse move */
	case CV_EVENT_MOUSEMOVE:
		/* draw a rectangle */

		break;
	}
}

void callback(const sensor_msgs::Image::ConstPtr& rgbImageMsg,
		const sensor_msgs::Image::ConstPtr& depthImageMsg,
		const sensor_msgs::CameraInfo::ConstPtr& rgbIntrinsicParamsMsg,
		const sensor_msgs::CameraInfo::ConstPtr& depthIntrinsicParamsMsg
		) {
	cv::Mat rgbImage = cv_bridge::toCvCopy(rgbImageMsg)->image;
	cv::cvtColor(rgbImage,rgbImage,CV_RGB2BGR);
	cv::Mat depthImage = cv_bridge::toCvCopy(depthImageMsg)->image;

	rgbLatestImage = rgbImage;
	depthLatestImage = depthImage;

	cv::imshow("color", rgbImage);
	cv::imshow("depth", depthImage*0.2);
	cv::waitKey(3);
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "rgbd_filewriter");

	ros::NodeHandle nh;

	message_filters::Subscriber<sensor_msgs::Image> rgbImageSubscriber(nh,"camera/rgb/image_color", 1);
	message_filters::Subscriber<sensor_msgs::Image> depthImageSubscriber(nh,"camera/depth/image", 1);
	message_filters::Subscriber<sensor_msgs::CameraInfo> rgbCamInfoSubscriber(nh, "camera/rgb/camera_info", 1);
	message_filters::Subscriber<sensor_msgs::CameraInfo> depthCamInfoSubscriber(nh, "camera/depth/camera_info", 1);

	typedef message_filters::sync_policies::ApproximateTime<
			sensor_msgs::Image,
			sensor_msgs::Image,
			sensor_msgs::CameraInfo,
			sensor_msgs::CameraInfo
			> MySyncPolicy;
	message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10),
			rgbImageSubscriber,depthImageSubscriber,rgbCamInfoSubscriber,depthCamInfoSubscriber);
	sync.registerCallback(boost::bind(&callback, _1, _2, _3, _4));

	cv::namedWindow("depth");
	cv::namedWindow("color");
	cvSetMouseCallback("depth", mouseHandler, NULL);

	ros::spin();
}
