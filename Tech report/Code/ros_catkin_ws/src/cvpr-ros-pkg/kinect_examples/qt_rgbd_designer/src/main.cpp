
#include <ros/ros.h>
#include <QtGui/QApplication>
#include "MainWindow.h"
//#include <articulation_msgs/TrackMsg.h>



using namespace std;




int main(int argc, char** argv) {
	ros::init(argc, argv, "stub");



	//cv::namedWindow("depth");
	//cv::namedWindow("color");

	//ros::spin();

	QApplication app( argc, argv );
	MainWindow win;
	win.show();
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();

	//while(true) {
		//app.processEvents();
		//ros::spinOnce();
	//}
}
