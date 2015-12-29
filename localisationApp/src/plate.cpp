
#include <iostream>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tesseract/baseapi.h>

#include "../inc/plate.hpp"

// CTOR
Plate::Plate(const std::string &path) : _path(path), _source(Image(path)) {
	cv::namedWindow("PlateRecognition", cv::WINDOW_AUTOSIZE );
}

// DTOR 
Plate::~Plate(){}
	
bool Plate::computeCalculation(bool display = false){
	// Convert Image To Grey
	this->_grey = this->_source.toGrey();
	// Remove Noise
	this->_grey.blur(BLUR_X, BLUR_Y);
	// Find Vertical Line 
	Image sobel = this->_grey.sobel(CV_8U, SOBEL_XORDER, SOBEL_YORDER);
	Image threshold = sobel.thresholdOtsu();
	threshold.getPlateRegion(15, 3);
	threshold.findContours();
	threshold.getRotatedRectangle();
	this->_possiblePlate = threshold.getPossiblePlates(this->_source.getImage());
	return (true);
}


