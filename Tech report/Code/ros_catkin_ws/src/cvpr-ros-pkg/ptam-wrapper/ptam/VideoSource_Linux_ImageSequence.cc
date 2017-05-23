// Copyright 2008 Isis Innovation Limited
#include "VideoSource.h"
#include <cvd/diskbuffer2.h>
#include <cvd/colourspace_convert.h>
#include <cvd/colourspaces.h>

using namespace CVD;
using namespace std;

VideoSource::VideoSource()
{
  cout << "  VideoSource_Linux: Opening video source..." << endl;
  DiskBuffer2<CVD::Rgb<CVD::byte>>* pvb= new DiskBuffer2<CVD::Rgb<CVD::byte>>(globlist("~/Images/lab*.jpg"), 25);
  mptr = pvb;
  mirSize = pvb->size();
  cout << "  ... got video source." << endl;
};

ImageRef VideoSource::Size()
{ 
  return mirSize;
};

void VideoSource::GetAndFillFrameBWandRGB(Image<byte> &imBW, Image<Rgb<byte> > &imRGB)
{
	DiskBuffer2<CVD::Rgb<CVD::byte>>* pvb = (DiskBuffer2<CVD::Rgb<CVD::byte>>*) mptr;
	DiskBuffer2Frame<yuv411> *pVidFrame = pvb->get_frame();
  convert_image(*pVidFrame, imBW);
  convert_image(*pVidFrame, imRGB);
  pvb->put_frame(pVidFrame);
}
