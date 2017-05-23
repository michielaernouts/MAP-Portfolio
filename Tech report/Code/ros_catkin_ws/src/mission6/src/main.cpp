#include <cstdlib>
#include <iostream>


#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_datatypes.h>
#include <mavros_msgs/OverrideRCIn.h>

int RC_Param(std::string s, int i);

int main(int argc, char **argv)
{

    int rate = 20;

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
    /*ros::ServiceClient cl = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
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
    srv_takeoff.request.altitude = 3;
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
	
	//Change flight mode to ALT_HOLD
	/*srv_setMode.request.custom_mode = "ALT_HOLD";
	if(cl.call(srv_setMode)){
        	ROS_INFO("setmode send ok %d value:", srv_setMode.response.success);
    	}else{
        	ROS_ERROR("Failed to set ALT_HOLD");
        return -1;
    	}*/


//////createQuaternionMsgFromRollPitchYaw/////////////
//////////////////////////////////////////////////////

	//pose publisher
	ros::Publisher local_pos_pub = n.advertise<geometry_msgs::PoseStamped>("/erlecopter/ground_truth/pose",10);	
	geometry_msgs::PoseStamped poseMsg;

	//move 1 (yaw rotation)
	poseMsg.pose.position.x = 0;
	poseMsg.pose.position.y = 0;
	poseMsg.pose.position.z = 3;
	poseMsg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0.0,0.0,0.0);  //set initial orientation
	
	double rotation = poseMsg.pose.orientation.z;
	ROS_INFO("Start rotation is %f radians",rotation);
	ROS_INFO("QUATERNIONS: %f, %f, %f, %f ", poseMsg.pose.orientation.x, poseMsg.pose.orientation.y, poseMsg.pose.orientation.z, poseMsg.pose.orientation.w);
	
   	for(int i = 314; ros::ok() && i > 0; --i){  //Turn 180 degrees = 3.14 radians

		rotation = rotation + 0.01;
		poseMsg.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw (0.0,0.0,rotation);
		local_pos_pub.publish(poseMsg);
        	ros::spinOnce();
       	 	r.sleep();	
    	}
	ROS_INFO("End rotation is %f radians",rotation);
	ROS_INFO("QUATERNIONS: %f, %f, %f, %f ", poseMsg.pose.orientation.x, poseMsg.pose.orientation.y, poseMsg.pose.orientation.z, poseMsg.pose.orientation.w);
	


//////RC override/////////////
//////////////////////////////

	/*Zros::Publisher rc_override_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 10);

    	mavros_msgs::OverrideRCIn msg_override;
    	for(int i = 100; ros::ok() && i > 0; --i){
		msg_override.channels[0] = 1500;
		msg_override.channels[1] = 1500;
		msg_override.channels[2] = 1800;
		msg_override.channels[3] = 1500;
		msg_override.channels[4] = 1100;
		msg_override.channels[5] = 1100;
		msg_override.channels[6] = 1100;
		msg_override.channels[7] = 1100;

		rc_override_pub.publish(msg_override);
		ros::spinOnce();
		r.sleep();
    	}*/




    ////////////////////////////////////////////
    ///////////////////LAND/////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient land_cl = n.serviceClient<mavros_msgs::CommandTOL>("/mavros/cmd/land");
    mavros_msgs::CommandTOL srv_land;
    srv_land.request.altitude = 3;
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

