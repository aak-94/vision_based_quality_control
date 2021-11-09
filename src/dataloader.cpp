#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "dataloader.h"

using namespace std;

cv::Mat dataloader::load(string path)
{	
	/* function for displaying of images
	* Input:
	* string containing the path of the input image
	* Output:
	* Gray Image: grayscale image
	*/
	cv::Mat img_g, img_gray;
	cv::Mat img = cv::imread(path);
	cv::cvtColor(img, img_g, cv::COLOR_BGR2GRAY);
	
	return img_g;
}

cv::Mat dataloader::scale4(cv::Mat img)
{
	/* function for displaying of images
	* Input:
	* grayscale image
	* Output:
	* grayscale image scaled by 4 times in both directions
	*/
	cv::Mat img_gray;
	cv::resize(img, img_gray, cv::Size(img.rows * 4, img.cols * 4));
	return img_gray;
}
