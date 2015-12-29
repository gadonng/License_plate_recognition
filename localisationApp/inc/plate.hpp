#ifndef __PLATE__HPP__
#define __PLATE__HPP__

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#include "image.hpp"

// OPENCV COMPUTATION DEFINE
#define BLUR_X 			5
#define BLUR_Y 			5

#define SOBEL_XORDER 	1
#define SOBEL_YORDER 	0
#define SOBEL_KSIZE 	3

class Plate {

	//ATTR
private:
	std::string 			_path;
	Image 					_source;
	Image 					_grey;
	std::vector<cv::Mat> 	_possiblePlate;
	cv::ml::ANN_MLP  		*ann;
	cv::ml::KNearest 		*knnClassifier;

public:
	// CTOR
	Plate(const std::string &path);

	// DTOR
	~Plate();

	bool computeCalculation(bool display);
};

#endif