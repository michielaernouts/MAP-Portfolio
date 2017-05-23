#include "SegmentMain.h"

SegmentMain::SegmentMain() {

  setWindowTitle("Segmentation Tool");

  calcSeg = new QAction(tr("Segment"), this);

  QToolBar *tb = addToolBar(tr("Actions"));
  tb->addAction(calcSeg);

  setCentralWidget(&segView);
  connect(calcSeg, SIGNAL(triggered()), this, SLOT(calcSegmentation()));
}


SegmentMain::~SegmentMain()
{
}

void SegmentMain::calcSegmentation() {

 segView.calcSegmentation();

}
SegmentView* SegmentMain::segmentView()
{
  return &segView;
}
