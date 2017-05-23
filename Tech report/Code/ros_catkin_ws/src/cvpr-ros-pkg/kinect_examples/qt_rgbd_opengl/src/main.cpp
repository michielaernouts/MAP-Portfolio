#include <stdio.h>
#include <ros/ros.h>
#include <QtGui/QApplication>




#include <KinectGLWidget.h>



int main(int argc, char *argv[])
{
	ros::init(argc, argv, "stub");

	QApplication app( argc, argv );

	KinectGLWidget widget;
	widget.show();
	widget.resize(640,480);
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	int result =  app.exec();
	fprintf(stderr,"\n\nExiting Program\n\n");
	return result;
}
