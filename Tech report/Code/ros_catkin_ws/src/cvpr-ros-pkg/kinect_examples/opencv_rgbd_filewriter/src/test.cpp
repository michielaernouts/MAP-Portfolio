/*
 * test.cpp
 *
 *  Created on: Jul 13, 2011
 *      Author: sturmju
 */

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv) {
	cv::namedWindow("testimage");

	cv::Mat img16(cv::Size(640,480),CV_16UC1);
	for(int y=0;y<480;y++) {
		for(int x=0;x<640;x++) {
			img16.at<unsigned short>(cv::Point(x,y)) = (unsigned short)x*100;
		}
	}

	cv::imshow("testimage",img16);
	cv::imwrite("/usr/wiss/sturmju/Desktop/test.png",img16);
	cv::waitKey(5000);

	return 0;
}
