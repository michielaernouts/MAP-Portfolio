/* 
 * A ROS interface for Cortex MoCap Streams
 * by Daniel Maier, based on an implementation by Joerg Mueller
 *
 */

#include <ros/ros.h>
#include <cortex_stream/cortex.h>
#include <map>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Vector3.h>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
using namespace std;


// Publisher for marker message
ros::Publisher marker_pub;

// Class containing callbacks, bodies, etc.
class MocapInterface
{
   public:
      MocapInterface();
      void processOnce();
      int cortexRequestPort;
      int cortexMulticastPort;
      std::string cortexAddress;
      void handleCortexFrame(void *frame);
   protected:
      double conversionFactor; // [meters per MoCap units]
      double requestCortexTimeout; // [s]
      double frameRate; // [Hz]
      struct BodyDefinition {
         std::vector<std::string> markerNames;
      };
      boost::recursive_mutex marker_array_msg_lock_;
      visualization_msgs::MarkerArray markerArrayMsg;
      std::map<std::string, BodyDefinition> body;
      std::string marker_frame_id_;
};

// Constructor using ROS params 
MocapInterface::MocapInterface()
{
   ros::NodeHandle nh;
   ros::NodeHandle private_nh("~");
   private_nh.param("cortexRequestPort", cortexRequestPort, 1510); 
   private_nh.param("cortexMulticastPort", cortexMulticastPort, 1509); 
   private_nh.param("cortexAddress", cortexAddress, std::string("132.230.167.153")); 
   private_nh.param("markerFrameId", marker_frame_id_, std::string("/mocap")); 
   conversionFactor = 0.001; // meters per MoCap unit
   requestCortexTimeout = 0.5; // seconds
}

// Corext Data Handler is called everytime new data is recieved from the cortex thread
// this has to be global, so we call the actual handler (member function) in here
void CortexDataHandler(sFrameOfData* frame, void *params)
{
   ((MocapInterface*)params)->handleCortexFrame(frame);
}


// Actual handler for processing a frame of the Cortex Data Stream
void MocapInterface::handleCortexFrame(void *frame)
{
   sFrameOfData *f = (sFrameOfData*)frame;
   ros::Time timestamp = ros::Time::now() - ros::Duration(f->fDelay); // TODO: subtract network transfer delay

   double scale_fac = 0.05;
   sBodyData *b = f->BodyData;
   markerArrayMsg.markers.clear();
   boost::recursive_mutex::scoped_lock marker_array_msglock(marker_array_msg_lock_);
   // loop over all bodies in that frame
   for (int i=0; i<f->nBodies; i++, b++) {
      visualization_msgs::Marker markerMsg;
      markerMsg.type = visualization_msgs::Marker::SPHERE_LIST;
      markerMsg.header.frame_id = marker_frame_id_;
      markerMsg.header.stamp = timestamp;
      markerMsg.action = visualization_msgs::Marker::ADD;
      markerMsg.id = 0; // marker id is 0, because we use a different namespace for every body
      markerMsg.ns = b->szName; // marker namespace is body name
      markerMsg.points.clear();
      // set color for markers of that body (TODO: colorize markers belonging to different bodies differently)
      markerMsg.color.r = 1.0;
      markerMsg.color.g = 1.0;
      markerMsg.color.b = 1.0;
      markerMsg.color.a = 1.0;
      markerMsg.scale.x = scale_fac;
      markerMsg.scale.y = scale_fac;
      markerMsg.scale.z = scale_fac;
      geometry_msgs::Pose pose;
      // body pose is not known (requires some model fitting and tracking) 
      // so set body origin to (0,0,0) and alter marker positions instead
      pose.position.x = 0;
      pose.position.y = 0;
      pose.position.z = 0;
      pose.orientation.x = 0;
      pose.orientation.y = 0;
      pose.orientation.z = 0;
      pose.orientation.w = 1;
      // process all markers for that body
      // watch out here, because we are losing the association between a marker's id as defined 
      // in the body definition and the marker index in the ROS markerArray message
      // this is no problem for visualization but for further processing (e.g. tracking)
      // TODO: fix this (requires a new ROS data structure)
      for (int j=0; j<b->nMarkers; j++) {
          geometry_msgs::Point p;
         // marker not detected by Cortex 
         if (b->Markers[j][0] == XEMPTY &&
               b->Markers[j][1] == XEMPTY &&
               b->Markers[j][2] == XEMPTY) {
			 p.x = numeric_limits<float>::quiet_NaN ();
			 p.y = numeric_limits<float>::quiet_NaN ();
			 p.z = numeric_limits<float>::quiet_NaN ();
         } else {
			 p.x = b->Markers[j][0]*conversionFactor;
			 p.y = b->Markers[j][1]*conversionFactor;
			 p.z = b->Markers[j][2]*conversionFactor;
         }
         markerMsg.points.push_back(p);
         // ignore marker names right now
         // this is what we should do:
         // markerMsg.body[b->szName].marker[body[b->szName].markerNames[j]] = m;
      }
      markerArrayMsg.markers.push_back(markerMsg);
   }
   marker_pub.publish(markerArrayMsg);
}

// global Error Msg Handler for Cortex
void CortexErrorMsgHandler(int iLevel, const char *szMsg, void*)
{
   if (iLevel == VL_Debug) {
      ROS_DEBUG("Cortex: %s", szMsg);
   } else if (iLevel == VL_Info) {
      ROS_INFO("Cortex: %s", szMsg);
   } else if (iLevel == VL_Warning) {
      ROS_WARN("Cortex: %s", szMsg);
   } else if (iLevel == VL_Error) {
      ROS_ERROR("Cortex: %s", szMsg);
   } else {
      ROS_ERROR("Received unknown Cortex Error Msg");
   }
}

// Initialization of Cortex stream (e.g. body definitions, ports, etc)
void MocapInterface::processOnce()
{
   Cortex_SetVerbosityLevel(VL_Info);
   Cortex_SetErrorMsgHandlerFunc(CortexErrorMsgHandler, this);
   if (Cortex_SetRequestPort(cortexRequestPort) != RC_Okay)
      return;
   if (Cortex_SetMulticastPort(cortexMulticastPort) != RC_Okay)
      return;
   if (Cortex_Initialize(cortexAddress.c_str()) != RC_Okay) {
      std::cerr << "Unable to initialize Cortex client\n";
      return;
   }

   // request distance unit
   void *response = NULL;
   int numBytes = 0;
   int retval;
   retval = Cortex_Request("GetConversionToMillimeters", &response, &numBytes, requestCortexTimeout);
   if (retval != RC_Okay || numBytes != 4) {
      std::cerr << "Error: Failed to get conversion factor to millimeters\n";
      Cortex_Exit();
      return;
   }
   float factor;
   memcpy(&factor, response, 4);
   conversionFactor = factor/1000.0;
   std::cerr << "Got conversion factor " << conversionFactor << " meters per MoCap unit\n";

   // request frame rate
   numBytes = 0;
   retval = Cortex_Request("GetContextFrameRate", &response, &numBytes, requestCortexTimeout);
   if (retval != RC_Okay || numBytes != 4) {
      std::cerr << "Error: Failed to get frame rate\n";
      Cortex_Exit();
      return;
   }
   float rate;
   memcpy(&rate, response, 4);
   frameRate = rate;
   //std::cerr << "Got frame rate " << frameRate << " Hz\n";
   ROS_INFO("Got frame rate %4.2f Hz",frameRate);

   // request body definitions
   sBodyDefs *bodies = Cortex_GetBodyDefs(requestCortexTimeout);
   if (bodies == NULL) {
      std::cerr << "Error: Failed to get body definitions\n";
      Cortex_Exit();
      return;
   }
   // get bodies from cortex
   // a body consists of a name and a set of markers
   // every marker has a (unique) name 
   std::cerr << "Got body definitions:";
   sBodyDef *b = bodies->BodyDefs;
   for (int i=0; i<bodies->nBodyDefs; i++, b++) {
      BodyDefinition bd;
      bd.markerNames.reserve(b->nMarkers);
      for (int j=0; j<b->nMarkers; j++)
         bd.markerNames.push_back(b->szMarkerNames[j]);
      body[b->szName] = bd;
      std::cerr << " " << b->szName;
   }
   std::cerr << "\n";

   // start data handling
   Cortex_SetDataHandlerFunc(CortexDataHandler, this);
}


int main(int argc, char ** argv)
{
   ros::init(argc,argv,"cortex_stream");
   ros::NodeHandle nh;
   MocapInterface mocap; // create interface
   mocap.processOnce(); // call initialization
   marker_pub = nh.advertise<visualization_msgs::MarkerArray>( "cortex_marker_array", 0 );
   visualization_msgs::MarkerArray markerArrayMsg;
   ros::Rate r(100.0);
   while(ros::ok())
   {
      r.sleep();
      ros::spinOnce();
   }
   Cortex_Exit();
   ROS_INFO("Exit peacefully");
   return 0;
}
