#ifndef __IMAGE__HPP__
#define __IMAGE__HPP__

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#define MIN_PLATE_AREA 15
#define MAX_PLATE_AREA 125


class Image 
{
	// ATTR
	private:
		cv::Mat 								_image;
		std::vector<std::vector<cv::Point> > 	_contours;
		std::vector<cv::RotatedRect>			_rect;
	
	public:
		// CTOR
		Image();
		Image(const std::string &path);
		Image(cv::Mat &image);
		// DTOR
		~Image();

		// Getter
		cv::Mat 								&getImage();
		// Method 
		void 									display(const std::string &window);
		Image 									toGrey();
		void 									grey();
		void 									blur(int x, int y);
		Image 									sobel(int ddepth, int xorder, int yorder);
		Image 									thresholdOtsu();
		Image 									threshold(double thresh, double maxval, int type);
		void       								getPlateRegion(int x, int y);
		std::vector<std::vector<cv::Point> > 	&findContours();
		std::vector<cv::RotatedRect>			getRotatedRectangle();
		std::vector<cv::Mat> 					getPossiblePlates(cv::Mat &input);

	private:	
		bool  									checkSize(cv::RotatedRect &);
		cv::Mat 								getPossiblePlate(cv::RotatedRect rect, cv::Mat &input);

};

#endif