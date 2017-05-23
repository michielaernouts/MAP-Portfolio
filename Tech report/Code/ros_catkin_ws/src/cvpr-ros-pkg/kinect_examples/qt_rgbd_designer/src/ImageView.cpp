#include "ImageView.h"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <iostream>
#include <math.h>

using namespace std;

ImageView::ImageView(QWidget *parent)
  : QWidget(parent) {

  setPalette(QPalette(QColor(100, 100, 100)));
  setAutoFillBackground(true);
  
  image = 0;

}

ImageView::~ImageView() {

  if (image)
    delete image;

  
}



void ImageView::mousePressEvent(QMouseEvent *me) {



}

void ImageView::mouseMoveEvent(QMouseEvent *me) {


}

void ImageView::mouseReleaseEvent(QMouseEvent *me) {


}




void ImageView::paintEvent(QPaintEvent *) {
  
  QPainter painter(this);

  if (image)
    painter.drawImage(0, 0, *image);

}



