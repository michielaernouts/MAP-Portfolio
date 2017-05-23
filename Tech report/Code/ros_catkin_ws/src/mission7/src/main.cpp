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



ros::Publisher rc_override_pub;
mavros_msgs::OverrideRCIn msg_override;
ros::Publisher local_pos_pub;
ros::Subscriber sub;

bool altReady = false;
bool yawReady = false;

void override(int roll, int pitch, int throttle, int yaw){
    msg_override.channels[0] = roll;
    msg_override.channels[1] = pitch;
    msg_override.channels[2] = throttle;
    msg_override.channels[3] = yaw;
    msg_override.channels[4] = 65535; //65535 (-1) = ignore channel
    msg_override.channels[5] = 65535;
    msg_override.channels[6] = 65535;
    msg_override.channels[7] = 65535;
    rc_override_pub.publish(msg_override);
}

void takeoff(const geometry_msgs::PoseStamped& altMsg)
{
    if(ros::ok() && altMsg.pose.position.z < 3){   //TAKEOFF TO 3 METRES
        ROS_INFO("Going up");
        override(65535,65535,1600,65535);
        //altReady = false;
    }
    else{
        ROS_INFO("HOVER");
        override(65535,65535,1500,65535);  //HOVER
        altReady=true;
    }

    if(altReady){
        sub.shutdown();
        ROS_INFO("Subscriber shut down");
    }
}

void rotateYaw(const geometry_msgs::PoseStamped& yawMsg){

    ROS_INFO("Turning");
    override(65535,65535,65535,1800);
    /*if(ros::ok() && yawMsg.pose.orientation.z < 0){
        ROS_INFO("Turning");
        override(65535,65535,65535,1800);
        //yawReady = false;
    }
    else{
        ROS_INFO("Stop turning");
        override(65535,65535,65535,1500);
        yawReady=true;
    }

    if(altReady){
        sub.shutdown();
        ROS_INFO("Subscriber shut down");
    }*/
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "mavros_rc_override");
    int rate = 100;
    ros::NodeHandle n;

    ros::Rate r(rate);

    rc_override_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 10);
    local_pos_pub = n.advertise<geometry_msgs::PoseStamped>("/erlecopter/ground_truth/pose",10);

    ////////////////////////////////////////////
    /////////////////FLIGHT MODE////////////////
    ////////////////////////////////////////////
    ros::ServiceClient cl = n.serviceClient<mavros_msgs::SetMode>("/mavros/set_mode");
    mavros_msgs::SetMode srv_setMode;
    srv_setMode.request.base_mode = 0;
    srv_setMode.request.custom_mode = "STABILIZE";
    if (cl.call(srv_setMode)) {
        ROS_INFO("setmode send ok %d value:", srv_setMode.response.success);
    } else {
        ROS_ERROR("Failed to set flight mode");
        return -1;
    }

    ////////////////////////////////////////////
    ///////////////////ARM//////////////////////
    ////////////////////////////////////////////
    ros::ServiceClient arming_cl = n.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
    mavros_msgs::CommandBool srv;
    srv.request.value = true;
    if (arming_cl.call(srv)) {
        ROS_INFO("ARM send ok %d", srv.response.success);
    } else {
        ROS_ERROR("Failed arming or disarming");
    }

    ////////////////////////////////////////////
    /////////////////TAKEOFF////////////////////
    ////////////////////////////////////////////
    ROS_INFO("TAKEOFF");

    sub = n.subscribe("/erlecopter/ground_truth/pose", 10, &takeoff);

    while(!altReady && ros::ok()){
        ros::spinOnce();
        r.sleep();
    }


    ////////////////////////////////////////////
    /////////////////DO STUFF///////////////////
    /////////////////////////////////////////////
    //sleep(5);

    local_pos_pub = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",10);
	geometry_msgs::PoseStamped poseMsg;
    //move 1
    poseMsg.pose.position.x = 2;
    poseMsg.pose.position.y = 5;
    poseMsg.pose.position.z = 3;
    ROS_INFO("move 1");
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(poseMsg);
        ros::spinOnce();
        r.sleep();
    }

    /*sub = n.subscribe("/erlecopter/ground_truth/pose", 10, &rotateYaw);
    while(!yawReady && ros::ok()){
        ros::spinOnce();
        r.sleep();
    }*/
    //////createQuaternionMsgFromRollPitchYaw/////////////
    //////////////////////////////////////////////////////

	//pose publisher
	/*local_pos_pub = n.advertise<geometry_msgs::PoseStamped>("/erlecopter/ground_truth/pose",10);
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
	ROS_INFO("QUATERNIONS: %f, %f, %f, %f ", poseMsg.pose.orientation.x, poseMsg.pose.orientation.y, poseMsg.pose.orientation.z, poseMsg.pose.orientation.w);*/



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



