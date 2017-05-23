#include <cstdlib>

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

int main(int argc, char **argv)
{

    int rate = 10;

    ros::init(argc, argv, "mavros_takeoff");
    ros::NodeHandle n;

    ros::Rate r(rate);

    ////////////////////////////////////////////
    /////////////////GUIDED/////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient cl = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv_setMode;
    srv_setMode.request.base_mode = 0;
    srv_setMode.request.custom_mode = "GUIDED";
    if(cl.call(srv_setMode)){
        ROS_INFO("setmode send ok %d value:", srv_setMode.response.success);
    }else{
        ROS_ERROR("Failed SetMode");
        return -1;
    }

    ////////////////////////////////////////////
    ///////////////////ARM//////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient arming_cl = n.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    mavros_msgs::CommandBool srv;
    srv.request.value = true;
    if(arming_cl.call(srv)){
        ROS_INFO("ARM send ok %d", srv.response.success);
    }else{
        ROS_ERROR("Failed arming or disarming");
    }

    ////////////////////////////////////////////
    /////////////////TAKEOFF////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient takeoff_cl = n.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/takeoff");
    mavros_msgs::CommandTOL srv_takeoff;
    srv_takeoff.request.altitude = 1.5;
    srv_takeoff.request.latitude = 0;
    srv_takeoff.request.longitude = 0;
    srv_takeoff.request.min_pitch = 0;
    srv_takeoff.request.yaw = 0;
    if(takeoff_cl.call(srv_takeoff)){
        ROS_INFO("srv_takeoff send ok %d", srv_takeoff.response.success);
    }else{
        ROS_ERROR("Failed Takeoff");
    }

    ////////////////////////////////////////////
    /////////////////DO STUFF///////////////////
    ////////////////////////////////////////////
	sleep(5);
	
	//pose publisher
	ros::Publisher local_pos_pub = n.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",10);
	geometry_msgs::PoseStamped pose;
	
	//move 1
	pose.pose.position.x = 11;
	pose.pose.position.y = 0.5;
	pose.pose.position.z = srv_takeoff.request.altitude;
	ROS_INFO("Going to 10 0.5 1.25");
   	for(int i = 250; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	sleep(1);

	//move 2
	pose.pose.position.x = 11;
	pose.pose.position.y = 2;
	pose.pose.position.z = srv_takeoff.request.altitude;
	ROS_INFO("Going to 11 2 1.25");
   	for(int i = 100; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	sleep(1);

	//move 3
	pose.pose.position.x = -1.5;
	pose.pose.position.y = pose.pose.position.y;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("Going to -1.5 2 1.25");
   	for(int i = 300; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	sleep(2);

	//move 4
	pose.pose.position.x = pose.pose.position.x;
	pose.pose.position.y = -10;
	pose.pose.position.z = pose.pose.position.z;
	//pose.pose.orientation.z = 1.5708;  //turn the drone 90 degrees
	ROS_INFO("Going to -1.5 -11 1.25");	
	for(int i = 300; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	sleep(2);

	//move 5
	pose.pose.position.x = 7.5;
	pose.pose.position.y = pose.pose.position.y;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("Going to 7.5 -11 1.5");
   	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	sleep(2);

    ////////////////////////////////////////////
    ///////////////////LAND/////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient land_cl = n.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/land");
    mavros_msgs::CommandTOL srv_land;
    srv_land.request.altitude = srv_takeoff.request.altitude;
    srv_land.request.latitude = 0;
    srv_land.request.longitude = 0;
    srv_land.request.min_pitch = 0;
    srv_land.request.yaw = 0;
    if(land_cl.call(srv_land)){
        ROS_INFO("srv_land send ok %d", srv_land.response.success);
    }else{
        ROS_ERROR("Failed Land");
    }

    while (n.ok())
    {
      ros::spinOnce();
      r.sleep();
    }

    return 0;
}

