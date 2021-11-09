#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "utils.h"
#include "image_processing.h"
#include "dataloader.h"
#include "fft.h"

using namespace std;


int main()
{
	// variable declaration
	cv::Mat img_laplacian;

	//load & pre-process the input images
	string path = "resources/VIN_not_ok.png";
	cv::Mat img_gray = dataloader::load(path);
	cv::Laplacian(img_gray, img_laplacian, -1, 5);

	//load & pre-process the library images
	string lib_path = "resources/standard_m.png";
	cv::Mat lib_letter_gray = dataloader::load(lib_path);
	lib_letter_gray = dataloader::scale4(lib_letter_gray);

	//core processing
	int start_pos_x = 0;
	int start_pos_y = 0;
	utils::start_point(img_laplacian, &start_pos_x, &start_pos_y);
	cv::Mat extracted_patch = utils::extract_m(img_gray, start_pos_x, start_pos_y);
	cv::Mat extracted_patch_fft = fft::fft_shift(extracted_patch);
	cv::Mat lib_letter_fft = fft::fft_shift(lib_letter_gray);
	Image_processing matcher(extracted_patch_fft, lib_letter_fft);
	bool isFault = matcher.orb_matches();

	//display images
	cv::imshow("library_image", lib_letter_gray);
	cv::imshow("extracted_m", extracted_patch);
	if (isFault)
	{
		cout << "Error in vin punching" << endl;
	}
	else
	{
		cout << "Vin punching is ok" << endl;
	}
	cv::waitKey(10000);

	return 0;
}