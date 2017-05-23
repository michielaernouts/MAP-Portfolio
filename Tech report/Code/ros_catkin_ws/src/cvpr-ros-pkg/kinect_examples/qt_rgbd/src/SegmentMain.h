#ifndef SEGMENTMAIN_H_
#define SEGMENTMAIN_H_

#include <QtGui/qmainwindow.h>
#include <QtGui/qaction.h>
#include <QtGui/qtoolbar.h>

#include "SegmentView.h"

#include <iostream>

class SegmentMain : public QMainWindow {

 Q_OBJECT

 public:
  SegmentMain();
  ~SegmentMain();

  SegmentView* segmentView();

 private:
  SegmentView segView;
  QAction *calcSeg;

 private slots:
  void calcSegmentation();

};


#endif
