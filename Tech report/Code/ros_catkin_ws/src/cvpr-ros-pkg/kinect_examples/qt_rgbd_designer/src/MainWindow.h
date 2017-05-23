#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <ui_window.h>

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tf/transform_datatypes.h>
#include <iostream>

#include <QtCore/QTimer>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindow( QWidget * parent = 0, Qt::WFlags f = 0 );
	~MainWindow();


	ros::NodeHandle node;

	ros::Subscriber sub1;
	ros::Subscriber sub2;
	ros::Subscriber sub3;

	void infoDepthCallback(const sensor_msgs::CameraInfo::ConstPtr& msg) ;
	void imageDepthCallback(const sensor_msgs::Image::ConstPtr& msg);
	void imageColorCallback(const sensor_msgs::Image::ConstPtr& msg);


	QTimer *timer;

	public slots:
	void get_kinect_frame();

	private:
	sensor_msgs::CameraInfo::ConstPtr cameraInfo_;
	cv_bridge::CvImagePtr cv_ptr;
	cv::Mat debugImage_;

};


#endif
