#include <cstdlib>

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

int main(int argc, char **argv)
{

    int rate = 10;

    ros::init(argc, argv, "mavros_takeoff");
    ros::NodeHandle n;

    ros::Rate r(rate);
	
	/*ros::Publisher rc_override_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 10);

    	mavros_msgs::OverrideRCIn msg_override;

	msg_override.channels[0] = 1500;
	msg_override.channels[1] = 1500;
	msg_override.channels[2] = 1500;
	msg_override.channels[3] = 1500;
	msg_override.channels[4] = 1100;
	msg_override.channels[5] = 1100;
	msg_override.channels[6] = 1100;
	msg_override.channels[7] = 1100;

	rc_override_pub.publish(msg_override);
	ros::spinOnce();
	r.sleep();*/

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
    srv_takeoff.request.altitude = 1;
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
	pose.pose.position.x = 0;
	pose.pose.position.y = 2;
	pose.pose.position.z = srv_takeoff.request.altitude;
	ROS_INFO("move 1");
   	for(int i = 100; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 2
	pose.pose.position.x = 11;
	pose.pose.position.y = 2;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("move 2");
   	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 3
	pose.pose.position.x = -3;
	pose.pose.position.y = 1;
	pose.pose.position.z = 1.5;
	ROS_INFO("move 3");
   	for(int i = 240; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 4
	pose.pose.position.x = pose.pose.position.x;
	pose.pose.position.y = -11;
	pose.pose.position.z = pose.pose.position.z;
	//pose.pose.orientation.z = 1.5708;  //turn the drone 90 degrees
	ROS_INFO("move 4");	
	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 5
	pose.pose.position.x = 7.5;
	pose.pose.position.y = -10;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("move 5");
   	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 6
	pose.pose.position.x = 1.5;
	pose.pose.position.y = -10;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("move 6");
   	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

	//move 7
	pose.pose.position.x = 1.5;
	pose.pose.position.y = 0;
	pose.pose.position.z = pose.pose.position.z;
	ROS_INFO("move 5");
   	for(int i = 200; ros::ok() && i > 0; --i){
        	local_pos_pub.publish(pose);
        	ros::spinOnce();
       	 	r.sleep();
    	}

	//sleep(1);

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

