std::vector<cv::Point2f> corners;
	for (int i = 0; i < lines.size(); i++)
	{
    	for (int j = i+1; j < lines.size(); j++)
    	{
        	cv::Point2f pt = computeIntersect(lines[i], lines[j]);
        	if (pt.x >= 0 && pt.y >= 0)
            corners.push_back(pt);
    	}
	}
	std::vector<cv::Point2f> approx;
	cv::approxPolyDP(cv::Mat(corners), approx, 
                 cv::arcLength(cv::Mat(corners), true) * 0.02, true);
	/*
	if (approx.size() != 4)
	{
    	std::cout << "The object is not quadrilateral!" << std::endl;
    	return -1;
	}
	*/
	cv::Point2f center(0,0);
	for (int i = 0; i < corners.size(); i++)
    	center += corners[i];
	center *= (1. / corners.size());
	sortCorners(corners, center);

	// Define the destination image
	cv::Mat quad = cv::Mat::zeros(300, 220, CV_8UC3);

	// Corners of the destination image
	std::vector<cv::Point2f> quad_pts;
	quad_pts.push_back(cv::Point2f(0, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
	quad_pts.push_back(cv::Point2f(0, quad.rows));

	// Get transformation matrix
	cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);

	// Apply perspective transformation
	cv::warpPerspective(test.getImage(), quad, transmtx, quad.size());
	cv::imshow("PlateRecognition", quad);
	cv::waitKey(0);

cv::Point2f computeIntersect(cv::Vec4i a, cv::Vec4i b)
{
    int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
    int x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];

    if (float d = ((float)(x1-x2) * (y3-y4)) - ((y1-y2) * (x3-x4)))
    {
        cv::Point2f pt;
        pt.x = ((x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4)) / d;
        pt.y = ((x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4)) / d;
        return pt;
    }
    else
        return cv::Point2f(-1, -1);
}

void sortCorners(std::vector<cv::Point2f>& corners, cv::Point2f center)
{
    std::vector<cv::Point2f> top, bot;

    for (int i = 0; i < corners.size(); i++)
    {
        if (corners[i].y < center.y)
            top.push_back(corners[i]);
        else
            bot.push_back(corners[i]);
    }

    cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
    cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
    cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
    cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

    corners.clear();
    corners.push_back(tl);
    corners.push_back(tr);
    corners.push_back(br);
    corners.push_back(bl);
}

std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
	/*cv::findContours(this->_canny.getImage(), contours, hierarchy,
        cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        cv::Scalar color( rand()&255, rand()&255, rand()&255 );
		cv::drawContours(this->_source.getImage(), contours, idx, color, cv::FILLED, 8, hierarchy );
    }*/
	/*
    std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(this->_canny.getImage(), lines, 1, CV_PI/180, 70, 30, 10);
	int i = 0;
	while (i < lines.size()){
		cv::Point pt1(lines[i][0],lines[i][1]);
		cv::Point pt2(lines[i][2],lines[i][3]);
		cv::line(this->_source.getImage(), pt1,  pt2, cv::Scalar(0, 0, 255));
		i++;
	}*/
	cv::cornerHarris(this->_canny.getImage(),this->_canny.getImage(), 7, 5, 0);
	// Normalizing
    cv::Mat dst_norm, dst_norm_scaled;
    cv::normalize( this->_canny.getImage(), dst_norm, 0, 255, cv::NORM_MINMAX, 3134, cv::Mat() );
    cv::convertScaleAbs( dst_norm, dst_norm_scaled );
 
    // Drawing a circle around corners
    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
    {
        if( (int) dst_norm.at<float>(j,i) > 200 )
        {
          cv::circle( dst_norm_scaled, cv::Point( i, j ), 5,  cv::Scalar(0), 2, 8, 0 );
        }
    }
    }
    cv::imshow( "PlateRecognition", dst_norm_scaled );
	cv::waitKey(0);


    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(this->_canny.getImage(), contours, hierarchy,
        cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int idx = 0;
    
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        contours[idx] = this->findCorners(contours[idx]);
        cv::Scalar color( rand()&255, rand()&255, rand()&255 );
        if (display) {
            this->_source.display("PlateRecognition");
            cv::waitKey(0);
        }
    }
    if (display) {
        this->_source.display("PlateRecognition");
        cv::waitKey(0);
    }
