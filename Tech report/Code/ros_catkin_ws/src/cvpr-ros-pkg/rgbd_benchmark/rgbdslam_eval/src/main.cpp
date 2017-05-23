/* This file is part of RGBDSLAM.
 * 
 * RGBDSLAM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * RGBDSLAM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with RGBDSLAM.  If not, see <http://www.gnu.org/licenses/>.
 */

/* registration main:
 * Create 
 * - a Qt Application 
 * - a ROS Node, 
 * - a ROS listener, listening to and processing kinect data
 * - Let them communicate internally via QT Signals
 */
#include "openni_listener.h"
#include "qtros.h"
#include <QApplication>
#include <QObject>
#include "qtcv.h"
#include <Eigen/Core>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

#include "parameter_server.h"


//TODO:
//try ASIFT
//File dialog for Saving
//even better potential-edge-selection through flann
//subpixel accuracy for feature matches?
//Performance optimization
//Get all Parameters from Param server or command line
//Better separation of function, communication, parameters and gui

int main(int argc, char** argv)
{
 if(argc!=3) {
	 cerr <<"Usage: "<<endl;
	 cerr <<"rgbdslam <bagfile.bag> <trajectory.txt>"<<endl;
	 cerr <<endl;
	 cerr <<"Required topics:  /camera/rgb/image_mono, /camera/depth/image and /camera/rgb/points"<<endl;
	 cerr <<"If you use the dataset for evaluation, you can use the add_pointclouds_to_bagfile.py tool."<<endl;
	 return 0;
 }

 QApplication application(argc,argv);
 //create thread object, to run the ros event processing loop in parallel to the qt loop
 QtROS qtRos(argc, argv, "rgbdslam"); //ros node name

 //If one thread receives a exit signal from the user, signal the other thread to quit too
 QObject::connect(&application, SIGNAL(aboutToQuit()), &qtRos, SLOT(quitNow()));
 QObject::connect(&qtRos, SIGNAL(rosQuits()), &application, SLOT(quit()));

 ParameterServer* params = ParameterServer::instance();
 GraphManager graph_mgr(qtRos.getNodeHandle(), NULL);
 OpenNIListener kinect_listener(qtRos.getNodeHandle(), &graph_mgr,
                                params->get<std::string>("topic_image_mono").c_str(),
                                params->get<std::string>("topic_image_depth").c_str(),
                                params->get<std::string>("topic_points").c_str(),
                                params->get<std::string>("feature_extractor_type").c_str(),
                                params->get<std::string>("feature_detector_type").c_str());



  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  // create a nice name
  strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);

  std::clock_t starttime=std::clock();

  kinect_listener.graph_mgr_->reset();
  kinect_listener.restart_counting();

  // can break if file is corrupt
  try
  {
   kinect_listener.runBagFile(argv[1],argv[2]);
  }
  catch (rosbag::BagIOException ex)
  {
   ROS_INFO("fail");
  }

  cout << "callbacks: " << kinect_listener.callback_counter << " added: " << kinect_listener.cnt_added <<
     " (" << (kinect_listener.cnt_added*100/kinect_listener.callback_counter) << " %)" << endl;
  cout << "Finished after " << (( std::clock() - starttime ) / (double)CLOCKS_PER_SEC)  << "secs" << endl << endl;


  return 0;
}


