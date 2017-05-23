#ifndef SEGMENTVIEW_H_
#define SEGMENTVIEW_H_

#include <QtGui/qwidget.h>
#include <QtGui/qpen.h>
#include <cv_bridge/cv_bridge.h>

class SegmentView : public QWidget {

 Q_OBJECT

 public:

  SegmentView(QWidget *parent = 0);
  ~SegmentView();

  void calcSegmentation();
  void updateImage(cv::Mat& cvimage);

 protected:
  void paintEvent(QPaintEvent *pe);

 private:
  QImage *image;
};


#endif
