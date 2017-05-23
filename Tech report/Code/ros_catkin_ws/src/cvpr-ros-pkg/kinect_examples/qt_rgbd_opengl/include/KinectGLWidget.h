#ifndef KINECTGLWIDGET_H
#define KINECTGLWIDGET_H

#include <ros/ros.h>
#include <QtCore/QTimer>
#include <QtOpenGL/QGLWidget>

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>

class KinectGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	KinectGLWidget( QWidget * parent = 0, Qt::WFlags f = 0 );
	~KinectGLWidget();

	void display();

	virtual void	keyPressEvent ( QKeyEvent * event );

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
	cv_bridge::CvImagePtr color_ptr;
	cv_bridge::CvImagePtr depth_ptr;
	cv::Mat debugImage_;
	int images_recieved;

	double rotangle;
	double conn_threshold;
};



#endif
