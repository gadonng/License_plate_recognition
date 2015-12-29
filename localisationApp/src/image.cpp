#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../inc/image.hpp"

Image::Image() {
	
}

Image::Image(const std::string &path) {
	this->_image = cv::imread(path, 1);
}

Image::Image(cv::Mat &image) {
	this->_image = image;		
}

Image::~Image() {
}

cv::Mat &Image::getImage() {
	return (this->_image);
}

void Image::display(const std::string &window) {
	cv::imshow(window, this->_image);
}

Image Image::toGrey() {
	cv::Mat grey;
	cv::cvtColor(this->_image, grey, cv::COLOR_BGR2GRAY);
	Image result(grey);
	return result;
}

void Image::grey() {
	cv::cvtColor(this->_image, this->_image, cv::COLOR_BGR2GRAY);
}

void Image::blur(int x, int y) { 
	cv::blur( this->_image, this->_image, cv::Size(x,y));
}

Image Image::threshold(double thresh, double maxval, int type) {
	cv::Mat treshI;
	
	cv::threshold(this->_image, treshI, thresh,maxval, type);	
	return (Image(treshI));
}

Image Image::sobel(int ddepth, int xorder, int yorder) {
	cv::Mat gradX;
	cv::Sobel(this->_image, gradX, ddepth, xorder, yorder, 3, 1, 0);
	return (Image(gradX));
}

Image Image::thresholdOtsu() {
	cv::Mat tresh;

	cv::threshold(this->_image, tresh, 0, 255, cv::THRESH_OTSU + cv::THRESH_BINARY);

	Image result(tresh);
	return (result);
}

void Image::getPlateRegion(int x, int y){	
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(x,y));
	cv::morphologyEx(this->_image, this->_image, cv::MORPH_CLOSE, element);
}


std::vector<std::vector<cv::Point> > &Image::findContours(){
	cv::findContours(this->_image,this->_contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	return (this->_contours);
}

std::vector<cv::RotatedRect>	Image::getRotatedRectangle(){
	std::vector<cv::RotatedRect> result;
	std::vector<std::vector<cv::Point> >::iterator it = this->_contours.begin();

	while (it != this->_contours.end()){
		cv::RotatedRect rect = cv::minAreaRect(cv::Mat(*it));
		if (!this->checkSize(rect)){
			it = this->_contours.erase(it);
		}
		else {
			it++;
			result.push_back(rect);
		}
	}
	this->_rect = result;
	return (result);
}


std::vector<cv::Mat> Image::getPossiblePlates(cv::Mat &input){
	std::vector<cv::RotatedRect>::iterator		it = this->_rect.begin();
	std::vector<cv::Mat> 						result;

	while (it != this->_rect.end()){
		result.push_back(this->getPossiblePlate(*it, input));
		++it;
	}
	return (result);
}

// Private function 

bool  Image::checkSize(cv::RotatedRect &canditate){
	// TODO : Externalise variable
	// Error Aprox 40 %
	float error = 0.4;
	// Chinese  car plate size 440 * 14O = 3.14 ratio
	const float aspect = 3.1428;
	int  min = MIN_PLATE_AREA * aspect * MIN_PLATE_AREA; // Minimum rect area 
	int  max = MAX_PLATE_AREA * aspect * MAX_PLATE_AREA; // Minimum rect area 

	float rmin = aspect - aspect * error;
	float rmax = aspect + aspect * error;

	int area = canditate.size.height * canditate.size.width;

	float r = (float)canditate.size.height / (float)canditate.size.width;
	
	if (r < 1){
		r = 1/r;
	}
	if ((area < min || area > max) || (r < rmin || r > rmax))
		return (false);
	return (true);
}

cv::Mat Image::getPossiblePlate(cv::RotatedRect rect, cv::Mat &input) {
	float r = (float)rect.size.width / (float)rect.size.height;
	float angle = rect.angle;
	
	cv::Size rectSize = rect.size;
		
	cv::Mat imageCrop;
	
	if (r < 1) {
		angle = 90 + angle;
		cv::Mat rotMat = cv::getRotationMatrix2D(rect.center, angle, 1);
		cv::Mat imageRot;
		cv::warpAffine(input, imageRot, rotMat, input.size(),cv::INTER_CUBIC);
		cv::swap(rectSize.width, rectSize.height);
		cv::getRectSubPix(imageRot, rectSize, rect.center, imageCrop);
	}
	else  {
		cv::getRectSubPix(input, rectSize, rect.center, imageCrop);	
	}

	cv::Mat result;
	result.create(45, 145, CV_8UC3);
	cv::resize(imageCrop, result, result.size(), 0, 0, cv::INTER_CUBIC);

	cv::Mat greyRes;
	cv::cvtColor(result, greyRes, cv::COLOR_BGR2GRAY);
	cv::blur(greyRes, greyRes, cv::Size(3,3));
	cv::equalizeHist(greyRes, greyRes);
	cv::imshow("PlateRecognition", greyRes);
	cv::waitKey(0);
	return (greyRes);
}













