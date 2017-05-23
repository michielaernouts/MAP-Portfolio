#include "ros/ros.h"
#include "std_msgs/String.h"
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>

#include <sstream>

#include <sensor_msgs/PointCloud2.h>

typedef union
 {
 struct /*anonymous*/
 {
 unsigned char Blue;
 unsigned char Green;
 unsigned char Red;
 unsigned char Alpha;
 };
 float float_value;
 long long_value;
} RGBValue;

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<pcl::PointCloud<pcl::PointXYZRGB> > ("/surface", 5);

  pcl::PointCloud<pcl::PointXYZRGB> cloud_msg;
  cloud_msg.header.stamp = ros::Time::now();
  cloud_msg.header.frame_id = "/world";
  cloud_msg.is_dense = false;

  ros::Duration(0.5).sleep();

  for(int i=0;i<100;i++) {
  	pcl::PointXYZRGB pt;
  	pt.x = i;
  	pt.y = 0.0;
  	pt.z = 0.0;
  	RGBValue color;
  	color.Red = 255;
  	color.Green = 0;
  	color.Blue = 0;
  	color.Alpha = 0;
  	pt.rgb = color.float_value;

  	cloud_msg.push_back(pt);
  }

  chatter_pub.publish(cloud_msg);
  ros::spinOnce();

  ros::Duration(0.5).sleep();

  return 0;
}
 
