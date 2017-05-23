#include <cstdlib>

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/PositionTarget.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <mavros_msgs/OverrideRCIn.h>
#include <sensor_msgs/Imu.h>

sensor_msgs::Imu imu_data;
void imuCb(const sensor_msgs::Imu::ConstPtr& msg){
  imu_data = *msg;
  //ROS_INFO("IMU %f", imu_data.orientation.z);
}

void rotate(int duration, int yaw_channel, ros::Publisher rc_override_pub ,ros::Rate r){
    mavros_msgs::OverrideRCIn msg_override;
    double current_orientation_z = imu_data.orientation.z;

    for(int i = duration; ros::ok() && i > 0; --i){
        msg_override.channels[3] = yaw_channel; //override yaw channel to rotate
        rc_override_pub.publish(msg_override);
        ros::spinOnce();
        r.sleep();
    }
    
    /*double const eps = 0.05; // some error threshold
    abs(imu_data.orientation.z - -current_orientation_z) < eps; // similar enough?

    while(imu_data.orientation.z < -current_orientation_z+eps && imu_data.orientation.z > -current_orientation_z-eps){
        msg_override.channels[3] = yaw_channel; //override yaw channel to rotate
        rc_override_pub.publish(msg_override);
        ros::spinOnce();
        r.sleep();
    }*/

    for(int i = 10; ros::ok() && i > 0; --i){
        msg_override.channels[0] = 0;
        msg_override.channels[1] = 0;
        msg_override.channels[2] = 0; 
        msg_override.channels[3] = 0; //return RC control to RC transmitter
        msg_override.channels[4] = 0;
        msg_override.channels[5] = 0;
        msg_override.channels[6] = 0;
        msg_override.channels[7] = 0;
        rc_override_pub.publish(msg_override);
        ros::spinOnce();
        r.sleep();
    }
}


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
    srv_takeoff.request.altitude = 2;
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
	geometry_msgs::PoseStamped poseMsg;

    //rc publisher
    ros::Publisher rc_override_pub = n.advertise<mavros_msgs::OverrideRCIn>("/mavros/rc/override", 10);
    
    //imu subscriber
    ros::Subscriber imu_sub = n.subscribe<sensor_msgs::Imu>("/mavros/imu/data",1000, imuCb);


    /*//ROTATION TEST

    //// INSERT ROTATION HERE ////
    ROS_INFO("ROTATING");
    rotate(120,1450,rc_override_pub,r);*/


    //move 1
    poseMsg.pose.position.x = 1.5;
    poseMsg.pose.position.y = -2.5;
    poseMsg.pose.position.z = srv_takeoff.request.altitude;
    //poseMsg.pose.orientation = tf::createQuaternionMsgFromYaw (3.14);
    ROS_INFO("move 1");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //// INSERT ROTATION HERE ////
    ROS_INFO("move 2 (rotation)");
    rotate(100,1400,rc_override_pub,r);

    //move 3
    poseMsg.pose.position.x = 3;
    poseMsg.pose.position.y = -2.5;
    poseMsg.pose.position.z = srv_takeoff.request.altitude;
    ROS_INFO("move 3");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 4
    poseMsg.pose.position.x = 3;
    poseMsg.pose.position.y = -4.5;
    poseMsg.pose.position.z = srv_takeoff.request.altitude;
    ROS_INFO("move 4");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 5
    poseMsg.pose.position.x = 0;
    poseMsg.pose.position.y = -4.5;
    poseMsg.pose.position.z = srv_takeoff.request.altitude;
    ROS_INFO("move 5");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 6
    poseMsg.pose.position.x = 2.1;
    poseMsg.pose.position.y = 0;
    poseMsg.pose.position.z = 1.5;
    ROS_INFO("move 6");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 7
    poseMsg.pose.position.x = 2.1;
    poseMsg.pose.position.y = 3;
    poseMsg.pose.position.z = 1.5;
    ROS_INFO("move 7");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 8
    poseMsg.pose.position.x = 2.1;
    poseMsg.pose.position.y = 3;
    poseMsg.pose.position.z = 2;
    ROS_INFO("move 8");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    /*//// INSERT ROTATION HERE ////
    ROS_INFO("move 9 (rotation)");
    rotate(100,1400,rc_override_pub,r);*/

    //move 10
    poseMsg.pose.position.x = 2.1;
    poseMsg.pose.position.y = 3;
    poseMsg.pose.position.z = 1.5;
    ROS_INFO("move 10");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 11
    poseMsg.pose.position.x = 2.1;
    poseMsg.pose.position.y = 0;
    poseMsg.pose.position.z = 1.5;
    ROS_INFO("move 11");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    //move 12
    poseMsg.pose.position.x = 1.5;
    poseMsg.pose.position.y = -2.5;
    poseMsg.pose.position.z = 2;
    ROS_INFO("move 12");
    for(int i = 100; ros::ok() && i > 0; --i){
            local_pos_pub.publish(poseMsg);
            ros::spinOnce();
            r.sleep();
        }

    /*//// INSERT ROTATION HERE ////
    ROS_INFO("move 13 (rotation)");
    rotate(100,1400,rc_override_pub,r);*/


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

    srv.request.value = false;
    if(arming_cl.call(srv)){
        ROS_INFO("ARM send ok %d", srv.response.success);
    }else{
        ROS_ERROR("Failed arming or disarming");
    }
    while (n.ok())
    {
      ros::spinOnce();
      r.sleep();
    }

    return 0;
}



