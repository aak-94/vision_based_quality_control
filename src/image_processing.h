#pragma once

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

using namespace std;

class Image_processing
{
private:
	cv::Mat input_patch;
	cv::Mat lib_patch;
	
public:
	Image_processing(cv::Mat extracted_patch_fft, cv::Mat lib_letter_fft);
	bool orb_matches();
};