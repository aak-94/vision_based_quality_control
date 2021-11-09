#pragma once

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace std;

namespace dataloader
{
	cv::Mat load(string path);
	cv::Mat scale4(cv::Mat img);
}