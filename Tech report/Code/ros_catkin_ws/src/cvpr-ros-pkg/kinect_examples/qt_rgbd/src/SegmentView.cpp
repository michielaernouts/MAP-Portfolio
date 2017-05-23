#include "SegmentView.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <iostream>
#include <math.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

SegmentView::SegmentView(QWidget *parent)
  : QWidget(parent) {
  image = new QImage(640, 480, QImage::Format_RGB32);
  image->fill(qRgb(0, 0, 0));
}

SegmentView::~SegmentView() {

  if (image)
    delete image;

}


void SegmentView::paintEvent(QPaintEvent *) {

  QPainter painter(this);
  if (image)
    painter.drawImage(0, 0, *image);
}

void SegmentView::calcSegmentation() {

  update();
}

void SegmentView::updateImage(cv::Mat& cvimage)
{
//  cv::Mat debugImage;
//  cvtColor(cvimage * 0.2, debugImage, CV_GRAY2BGR);

    int size = cvimage.cols * cvimage.rows;
    int buffer[size];
    int* ptrOut = buffer;
    float* ptrIn = (float*)cvimage.data;
    uchar c=0;
    for(int i=0;i<size;i++) {
      c = (*ptrIn)*255;
      ptrIn++;
      *ptrOut = c<<16 | c<<8 | c;
      ptrOut++;
    }
  delete image;
  image = new QImage((uchar*)buffer,cvimage.cols,cvimage.rows, QImage::Format_RGB32);

  //  int w = cvimage.cols;
  //  int h = cvimage.rows;
//  if ((w != image->width()) || (h != image->height()))
//  {
//    delete image;
//    image = new QImage(640, 480, QImage::Format_RGB32);
//  }
//  for(int y=0;y<h;y++)
//    for(int x=0;x<w;x++) {
//      float c  = 255*cvimage.at<float>(cv::Point(x,y));
//      image->setPixel(x,y,qRgb(c,c,c));
//    }

  update();
}




