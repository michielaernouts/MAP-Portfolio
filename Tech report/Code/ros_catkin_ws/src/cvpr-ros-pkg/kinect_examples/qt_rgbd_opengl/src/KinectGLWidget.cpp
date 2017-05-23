
#include <KinectGLWidget.h>
#include <QtGui/QKeyEvent>


#include <math.h>

KinectGLWidget::KinectGLWidget( QWidget * parent, Qt::WFlags f) :
QGLWidget(parent), timer(0),
images_recieved(0),
rotangle(0.0),
conn_threshold(0.1)
{
	sub1 = node.subscribe("camera/depth/image", 1, &KinectGLWidget::imageDepthCallback,this);
	sub2 = node.subscribe("camera/depth/camera_info", 1,&KinectGLWidget::infoDepthCallback,this);
	sub3 = node.subscribe("camera/rgb/image_color", 1, &KinectGLWidget::imageColorCallback,this);

	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(get_kinect_frame()));
	timer->start();
}

KinectGLWidget::~KinectGLWidget()
{

}

void KinectGLWidget::get_kinect_frame()
{
	ros::spinOnce();
}


void KinectGLWidget::infoDepthCallback(const sensor_msgs::CameraInfo::ConstPtr& msg)
{
	cameraInfo_ = msg;
}

void KinectGLWidget::imageDepthCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	ros::Time begin = ros::Time::now();
	if (!cameraInfo_)
		return;
	try {
		depth_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	images_recieved |= 2;
	if(images_recieved == 3)
	{
		images_recieved = 0;
		display();
	}

}

void KinectGLWidget::imageColorCallback(const sensor_msgs::Image::ConstPtr& msg)
{
	ros::Time begin = ros::Time::now();
	if (!cameraInfo_)
		return;
	try {
		color_ptr = cv_bridge::toCvCopy(msg);
	} catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}
//	cv::cvtColor(cv_ptr->image,cv_ptr->image,CV_RGB2BGR);

  int w = color_ptr->image.cols;
  int h = color_ptr->image.rows;

  for(int y=0;y<h;y++)
    for(int x=0;x<w;x++)
    {
    	cv::Vec3f color = color_ptr->image.at<cv::Vec3b>(cv::Point(x,y));
    }

  images_recieved |= 1;
	if(images_recieved == 3)
	{
		images_recieved = 0;
		display();
	}
}

void KinectGLWidget::display()
{

	int nx = 640;
	int ny = 480;



//	glViewport(0, 0, nx, ny);

	if((double)width()/(double)nx*(double)ny > (double)height())
		glViewport(0,0,(int)((double)height()/(double)ny*(double)nx),height());
	else
		glViewport(0,0,width(),(int)((double)width()/(double)nx*(double)ny));


  double near = 0.001f;//dmin;
  double far = 100.0;
  double fx = cameraInfo_->K[0];
  double fy = cameraInfo_->K[4];
	double ox = -cameraInfo_->K[2];
	double oy = -cameraInfo_->K[5];
  double d, d_1;
  double davg = 1.0;

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);


  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(ox/fx*near,(nx+ox)/fx*near,oy/fy*near,(ny+oy)/fy*near,near,far);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-davg);
  glRotatef(rotangle,0,1,0);
  glTranslatef(0,0,davg);
	glEnable(GL_CULL_FACE);

	cv::Vec3f color;
	glBegin(GL_QUADS);
	for(int y=0;y<ny;y++)
	{
		for(int x=0;x<nx;x++)
		{
			//cv::Vec3f color = cv_ptr->image.at<cv::Vec3b>(cv::Point(x,y));
//			if(isfinite(frame->depth[nx*(ny-1-y)+x]))
			d = depth_ptr->image.at<float>(cv::Point(x,ny-1-y));
			if(std::isfinite(d))
			{
				color = color_ptr->image.at<cv::Vec3b>(cv::Point(x,ny-1-y));
				glColor3f((float)(color[0])/255.0,(float)(color[1])/255.0,(float)(color[2])/255.0);
				glVertex3f((ox+x+1)*d/fx, (oy+y)*d/fy,-d);
				glVertex3f((ox+x+1)*d/fx, (oy+y+1)*d/fy,-d);
				glVertex3f((ox+x)*d/fx, (oy+y+1)*d/fy,-d);
				glVertex3f((ox+x)*d/fx, (oy+y)*d/fy,-d);


				if(x<nx-1)
				{
					d_1 = depth_ptr->image.at<float>(cv::Point(x+1,ny-1-y));
					if(std::isfinite(d_1) &&  fabs(d_1 - d) < conn_threshold)
					{
						glVertex3f((ox+x+1)*d_1/fx, (oy+y)*d_1/fy,-d_1);
						glVertex3f((ox+x+1)*d_1/fx, (oy+y+1)*d_1/fy,-d_1);
						glVertex3f((ox+x+1)*d/fx, (oy+y+1)*d/fy,-d);
						glVertex3f((ox+x+1)*d/fx, (oy+y)*d/fy,-d);
					}
				}

				if(y<ny-1)
				{
					d_1 = depth_ptr->image.at<float>(cv::Point(x,ny-1-y-1));
						if(std::isfinite(d_1)&&  fabs(d_1 - d) < conn_threshold)
					{
						glVertex3f((ox+x)*d/fx,     (oy+y+1)*d/fy,-d);
						glVertex3f((ox+x+1)*d/fx,   (oy+y+1)*d/fy,-d);
						glVertex3f((ox+x+1)*d_1/fx, (oy+y+1)*d_1/fy,-d_1);
						glVertex3f((ox+x)*d_1/fx,   (oy+y+1)*d_1/fy,-d_1);
					}
				}
			}
		}
	}
	glEnd();

	swapBuffers();

}



void	KinectGLWidget::keyPressEvent ( QKeyEvent * event )
{
	if(event->key() == Qt::Key_Right)
	{
		rotangle += -1.0f;
		fprintf(stderr,"\nRotation Angle: %f",rotangle);
	}
	else if(event->key() == Qt::Key_Left)
	{
		rotangle += 1.0f;
		fprintf(stderr,"\nRotation Angle: %f",rotangle);
//		drawn = false;
//		redraw = false;
	}

	//display();
}

