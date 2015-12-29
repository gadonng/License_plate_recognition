#include <iostream>
#include <cstdlib>
#include "../inc/plate.hpp"

void usage() {
	std::cout << "Usage : ./plateRecognition pathToPlate1 [pathToPlate1] ..." << std::endl;
}

int main(int argc, char **argv) {
	
	if (argc <= 1) {
		usage();
		return (EXIT_FAILURE);
	}
	
	Plate plate(argv[1]);
	plate.computeCalculation(true);

	/*
	std::cout << lines.size() << std::endl;
	int i = 0;
	while (i < lines.size()){
		cv::Point pt1(lines[i][0],lines[i][1]);
		cv::Point pt2(lines[i][2],lines[i][3]);
		cv::line(test.getImage(), pt1,  pt2, cv::Scalar(0, 0, 255));
		i++;
	}

	test.display("PlateRecognition");
	cv::waitKey(0);
	*/
	return (EXIT_SUCCESS);
}