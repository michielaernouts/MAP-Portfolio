#include <QtGui/QApplication>
#include "SegmentMain.h"
#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tf/transform_datatypes.h>
#include <iostream>

cv_bridge::CvImagePtr cv_ptr;
SegmentMain* segMain;

using namespace std;

void imageCallback(const sensor_msgs::Image::ConstPtr& msg) {
    cout << "received image" << endl;
    ros::Time begin = ros::Time::now();
    try {
        cv_ptr = cv_bridge::toCvCopy(msg);
        segMain->segmentView()->updateImage(cv_ptr->image);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "stub");

  ros::NodeHandle n;

  QApplication app(argc, argv);

  segMain = new SegmentMain();

  segMain->show();
  segMain->setGeometry(50, 50, 640, 480);

  ros::Subscriber sub = n.subscribe("camera/depth/image", 1, imageCallback);

  while (true) {
    app.processEvents();
    ros::spinOnce();
  }
  //    return app.exec();

}
