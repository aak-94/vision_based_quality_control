#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "utils.h"

using namespace std;


void utils::start_point(cv::Mat img_laplacian, int* start_pos_x, int* start_pos_y)
{
	/* function for finding the start point coordinates of the first letter
	* Input:
	* img_laplacian: cv::Mat datatype for edge detected image
	* start_pos_x = adress for the starting poin's x coordinate
	* start_pos_y = adress for the starting poin's y coordinate
	* Output:
	* adresse to the X and Y coordinates, where the first letter starts
	*/
	int h, w;
	h = img_laplacian.rows;
	w = img_laplacian.cols;
	int a = img_laplacian.at<uchar>(0, 0);
	for (int column = 0; column < w; column++)
	{
		bool flag = false;
		for (int row = 0; row < h; row++)
		{
			int b = img_laplacian.at<uchar>(row, column);
			if (b > a)
			{
				*start_pos_x = column;
				*start_pos_y = row;
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
}
cv::Mat utils::extract_m(cv::Mat img_gray, int start_pos_x, int start_pos_y)
{
	cv::Mat extracted, extracted_letter;
	cv::Rect roi(start_pos_x - 2, start_pos_y - 2, 55, 48);
	extracted = img_gray(roi);
	cv::resize(extracted, extracted_letter, cv::Size(extracted.rows * 4, extracted.cols * 4));
	return extracted_letter;
}