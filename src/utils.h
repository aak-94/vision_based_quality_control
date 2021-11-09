#pragma once

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace utils
{
	void start_point(cv::Mat img_laplacian, int* start_pos_x, int* start_pos_y);
	cv::Mat extract_m(cv::Mat img_gray, int start_pos_x, int start_pos_y);
}