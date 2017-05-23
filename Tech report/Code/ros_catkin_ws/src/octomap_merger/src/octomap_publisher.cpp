#include "ros/ros.h"
#include "std_msgs/String.h"

#include <octomap/octomap.h>
#include <octomap_msgs/conversions.h>
#include <octomap/OcTree.h>

#include <visualization_msgs/MarkerArray.h>

#include <sstream>
#include <iostream>

void printUsage(char* self){
  std::cerr << "    USAGE: rosrun octomap_merger octomap_publisher <InputFile.bt>\n";
  std::cerr << "    This tool publishes the given .bt file to an Octomap message\n";
  exit(0);
}

int main(int argc, char **argv)
{
  if (argc != 2)
    printUsage(argv[0]);

  ros::init(argc, argv, "octomap_publisher");

  ros::NodeHandle n;

  std::string inputFile = "";
  inputFile = std::string(argv[1]);

  //publisher
  ros::Publisher octomap_pub = n.advertise<octomap_msgs::Octomap>("/occupied_cells_vis", 1);
  //ros::Publisher octomap_pub = n.advertise<visualization_msgs::MarkerArray>("/occupied_cells_vis", 1);
  ros::Rate loop_rate(10);

  octomap_msgs::Octomap octomap;
  octomap::OcTree myOctomap(inputFile);
  octomap_msgs::binaryMapToMsg(myOctomap, octomap);
  
  ROS_INFO("Publishing Octree to ROS message");
  
  octomap.header.frame_id = "/map";

  octomap_pub.publish(octomap);
  
  int count = 0;
  while (ros::ok())
  {
    

    ros::spinOnce();
  
    loop_rate.sleep();
    ++count;

    
  }


  return 0;
}