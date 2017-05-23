#include "MainWindow.h"
#include "invert.cuh"


MainWindow::MainWindow( QWidget * parent, Qt::WFlags f) :
QMainWindow(parent, f), timer(0)
{
	setupUi(this);


	sub1 = node.subscribe("camera/depth/image", 1, &MainWindow::imageDepthCallback,this);
	sub2 = node.subscribe("camera/depth/camera_info", 1,&MainWindow::infoDepthCallback,this);
	sub3 = node.subscribe("camera/rgb/image_color", 1, &MainWindow::imageColorCallback,this);

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(get_kinect_frame()));
	timer->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::get_kinect_frame()
{
	ros::spinOnce();
}


void MainWindow::infoDepthCallback(const sensor_msgs::CameraInfo::ConstPtr& msg) {
	cameraInfo_ = msg;
	std::cout << "received info" << std::endl;
}

void MainWindow::imageDepthCallback(const sensor_msgs::Image::ConstPtr& msg) {
	std::cout << "received depth image" << std::endl;
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
	ros::Time start = ros::Time::now();
	invert((float3*)debugImage_.data,(float3*)debugImage_.data,1.0f,debugImage_.cols,debugImage_.rows,&field_g,&pitch);
	ros::Time stop = ros::Time::now();
	std::cout <<"computation time: "<<(stop-start).toSec()<<"s"<<std::endl;

	cuda_delete(field_g);

  int w = debugImage_.cols;
  int h = debugImage_.rows;
  if (widget->image && ((w != widget->image->width()) || (h != widget->image->height())))
  {
    delete widget->image;
    widget->image = new QImage(w, h, QImage::Format_RGB32);
  }
  else if(!(widget->image))
  {
    widget->image = new QImage(w, h, QImage::Format_RGB32);
  }
  float r=0,g=0,b=0;
  for(int y=0;y<h;y++)
    for(int x=0;x<w;x++) {
   	cv::Vec3f color = debugImage_.at<cv::Vec3f>(cv::Point(x,y));
      r  = 255*color[0];
      g  = 255*color[1];
      b  = 255*color[2];
     widget->image->setPixel(x,y,qRgb(r,g,b));
    }
  widget->update();
	//cv::imshow("depth", debugImage_);
	//cv::waitKey(3);

}

void MainWindow::imageColorCallback(const sensor_msgs::Image::ConstPtr& msg) {
	std::cout << "received color image" << std::endl;
	ros::Time begin = ros::Time::now();
	if (!cameraInfo_)
		return;
	try {
		cv_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
//	cv::cvtColor(cv_ptr->image,cv_ptr->image,CV_RGB2BGR);


  int w = cv_ptr->image.cols;
  int h = cv_ptr->image.rows;
  if (widget_2->image && ((w != widget_2->image->width()) || (h != widget_2->image->height())))
  {
    delete widget_2->image;
    widget_2->image = new QImage(w, h, QImage::Format_RGB32);
  }
  else if(!(widget_2->image))
  {
    widget_2->image = new QImage(w, h, QImage::Format_RGB32);
  }
  for(int y=0;y<h;y++)
    for(int x=0;x<w;x++) {
   	cv::Vec3f color = cv_ptr->image.at<cv::Vec3b>(cv::Point(x,y));
     widget_2->image->setPixel(x,y,qRgb(color[0],color[1],color[2]));
    }
  widget_2->update();
	//cv::imwrite(fname+"-color.png",cv_ptr->image);

	//cv::imshow("color", cv_ptr->image);
	//cv::waitKey(3);

}
