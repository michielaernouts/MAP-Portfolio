/*
 * convert16to8bit.cpp
 *
 *  Created on: Jul 14, 2011
 *      Author: sturmju
 */

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char** argv) {
	if(argc !=4 ){
		cerr << "Usage: convert16to8bit <16bit.png> <8bit.png> <scale>" << endl;
		return 0;
	}
	double scale = atof(argv[3]);
	cv::Mat depth16bit = cv::imread(argv[1]);
	cv::Mat depth8bit;
	depth16bit.convertTo(depth8bit, CV_8UC1, scale, 0);
	cv::imwrite(argv[2], depth8bit);

	return 0;
}
