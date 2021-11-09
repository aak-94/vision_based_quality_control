#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "fft.h"

void calculateDFT(cv::Mat& scr, cv::Mat& dst)
{
	// define mat consists of two mat, one for real values and the other for complex values
	cv::Mat planes[] = { scr, cv::Mat::zeros(scr.size(), CV_32F) };
	cv::Mat complexImg;
	cv::merge(planes, 2, complexImg);

	cv::dft(complexImg, complexImg);
	dst = complexImg;
}
void fftshift(const cv::Mat& input_img, cv::Mat& output_img)
{
	output_img = input_img.clone();
	int cx = output_img.cols / 2;
	int cy = output_img.rows / 2;
	cv::Mat q1(output_img, cv::Rect(0, 0, cx, cy));
	cv::Mat q2(output_img, cv::Rect(cx, 0, cx, cy));
	cv::Mat q3(output_img, cv::Rect(0, cy, cx, cy));
	cv::Mat q4(output_img, cv::Rect(cx, cy, cx, cy));

	cv::Mat temp;
	q1.copyTo(temp);
	q4.copyTo(q1);
	temp.copyTo(q4);
	q2.copyTo(temp);
	q3.copyTo(q2);
	temp.copyTo(q3);

}
cv::Mat fft::fft_shift(cv::Mat scr_img)
{
	scr_img.convertTo(scr_img, CV_32F);
	// expand input image to optimal size
	cv::Mat padded;
	int m = cv::getOptimalDFTSize(scr_img.rows);
	int n = cv::getOptimalDFTSize(scr_img.cols);
	cv::copyMakeBorder(scr_img, padded, 0, m - scr_img.rows, 0, n - scr_img.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
	// calculate DFT
	cv::Mat DFT_image;
	calculateDFT(padded, DFT_image);
	/*
	The result of the transformation is complex numbers.
	Displaying this is possible via a magnitude.
	*/
	cv::Mat real, imaginary;
	cv::Mat planes[] = { real, imaginary };

	cv::split(DFT_image, planes);
	cv::Mat mag_image;
	cv::magnitude(planes[0], planes[1], mag_image);

	cv::Mat shifted_DFT;
	fftshift(mag_image, shifted_DFT);

	// switch to a logarithmic scale
	shifted_DFT += cv::Scalar::all(1);
	cv::log(shifted_DFT, shifted_DFT);
	shifted_DFT = 20 * shifted_DFT;
	shifted_DFT = shifted_DFT(cv::Rect(0, 0, shifted_DFT.cols & -2, shifted_DFT.rows & -2));

	//cv::normalize(shifted_DFT, shifted_DFT, 0, 1, cv::NORM_MINMAX);
	shifted_DFT.convertTo(shifted_DFT, CV_8UC1);   
	//cout << shifted_DFT << endl;
	return shifted_DFT;
}