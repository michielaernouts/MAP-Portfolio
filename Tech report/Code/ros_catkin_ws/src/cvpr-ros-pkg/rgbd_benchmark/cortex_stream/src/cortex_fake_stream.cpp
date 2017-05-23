#include <ros/ros.h>
#include <cortex_stream/cortex.h>
#include <map>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
//#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <cmath>
#include <time.h>
using namespace std;
using namespace visualization_msgs;

visualization_msgs::MarkerArray markerArrayMsg;

void populate_marker_msg()
{
   // define 4 props
   Marker freespace;
   Marker nao;
   Marker box_obstacle_1;
   Marker box_obstacle_2;

   geometry_msgs::Point p;
   p.x = -0.5; p.y = -0.75; p.z = 1.1;
   freespace.points.push_back(p);
   p.x = 4.5; p.y = -0.7; p.z = 0.8;
   freespace.points.push_back(p);
   p.x = 4.4; p.y = 3.3; p.z = 1.1;
   freespace.points.push_back(p);
   p.x = -0.45; p.y = 3.4; p.z = 1.0;
   freespace.points.push_back(p);

   geometry_msgs::Point box_origin;
   double box_size_x = 0.4;
   double box_size_y = 0.2;
   double box_size_z = 0.2;
   double box_rotation = 1.0; // rad
   static double offset_x = 0.0;
   static double offset_y = 0.0;
   box_origin.x = 2.5 + offset_x; box_origin.y = 0.5 + offset_y ; box_origin.z = box_size_z;
   //offset_x += 0.002;
   //offset_y += 0.002;
   offset_x += (rand()%100 - 50)/2000.0; // uniform in range 
   offset_y += (rand()%100 - 50)/2000.0; // uniform in range of [0.025, 0.025]m
   box_obstacle_1.points.push_back(box_origin);
   p.x = box_origin.x + box_size_x; p.y = box_origin.y; p.z = box_origin.z - 0.03;
   box_obstacle_1.points.push_back(p);
   p.y += box_size_y; p.z += 0.02;
   box_obstacle_1.points.push_back(p);
   p.x -= box_size_x; p.z -= 0.01;
   box_obstacle_1.points.push_back(p);

   static int drop_out_counter = 0;
   static bool drop_out = false;
   if( drop_out_counter % 50 == 0) // flip
   {
      drop_out = !drop_out;
   }

   box_origin.x = 2.0 + offset_y; box_origin.y = 1.0 + offset_x; box_origin.z = box_size_z;
   box_obstacle_2.points.push_back(box_origin);
   p.x = box_origin.x + box_size_x; p.y = box_origin.y; p.z = box_origin.z - 0.03;
   box_obstacle_2.points.push_back(p);
   p.y += box_size_y; p.z += 0.02;
   box_obstacle_2.points.push_back(p);
   p.x -= box_size_x; p.z -= 0.01;
   if(!drop_out)
   box_obstacle_2.points.push_back(p);
   drop_out_counter ++;




   markerArrayMsg.markers.clear();
   vector<string> object_names;
   markerArrayMsg.markers.push_back(freespace);
   object_names.push_back("map_free_space_boundings");
   //markerArrayMsg.markers.push_back(nao);
   markerArrayMsg.markers.push_back(box_obstacle_1);
   object_names.push_back("box_obstacle_3");
   markerArrayMsg.markers.push_back(box_obstacle_2);
   object_names.push_back("box_obstacle_4");

   int cnt = 0; // TODO: randomize this 
   double scale_fac = 0.1;
   for(MarkerArray::_markers_type::iterator it = markerArrayMsg.markers.begin(); it!=markerArrayMsg.markers.end(); ++it, ++cnt)
   {
      visualization_msgs::Marker & markerMsg = *it;
      markerMsg.type = visualization_msgs::Marker::SPHERE_LIST;
      markerMsg.header.frame_id = "/mocap";
      markerMsg.action = visualization_msgs::Marker::ADD;
      // stamp is missing
      markerMsg.id = cnt;
      markerMsg.ns = object_names[cnt];
      markerMsg.color.r = 1.0;
      markerMsg.color.g = 0.0;
      markerMsg.color.b = 0.0;
      markerMsg.color.a = 1.0;
      markerMsg.scale.x = scale_fac;
      markerMsg.scale.y = scale_fac;
      markerMsg.scale.z = scale_fac;
      geometry_msgs::Pose pose;
      pose.position.x = 0;
      pose.position.y = 0;
      pose.position.z = 0;
   }


}

int main(int argc, char ** argv)
{

   ros::init(argc,argv,"cortex_fake_stream");
   ros::NodeHandle nh;
   ros::Rate r(20.0);
   srand ( time(NULL) );

   ros::Publisher marker_pub = nh.advertise<visualization_msgs::MarkerArray>( "cortex_marker_array", 0 );
   while(ros::ok())
   {
      populate_marker_msg();
      r.sleep();
      ros::Time timestamp = ros::Time::now()-ros::Duration(0.1);
      int cnt = 0;
      for(MarkerArray::_markers_type::iterator it = markerArrayMsg.markers.begin(); it!=markerArrayMsg.markers.end(); ++it )
      {
         visualization_msgs::Marker & markerMsg = *it;
         markerMsg.header.stamp = timestamp;
         ++cnt;
      }
      ROS_INFO("Publishing %d markers",cnt);
      marker_pub.publish(markerArrayMsg);
      ros::spinOnce();
   }
   ROS_INFO("Exit peacefully");
   return 0;
}
