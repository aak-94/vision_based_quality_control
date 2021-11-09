#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <string>
#include "image_processing.h"

using namespace std;

Image_processing::Image_processing(cv::Mat extracted_patch_fft, cv::Mat lib_letter_fft)
{
	input_patch = extracted_patch_fft;
	lib_patch = lib_letter_fft;
}

bool Image_processing::orb_matches()
{
	//declarations
	vector<cv::KeyPoint> keypoints_in, keypoints_lib;
	cv::Mat descriptors_in, descriptors_lib;

	//ORB object with detector, descriptor and matcher
	cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
	cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");

	// find the keypoints and descriptors with ORB
	detector->detect(input_patch, keypoints_in);
	detector->detect(lib_patch, keypoints_lib);
	descriptor->compute(input_patch, keypoints_in, descriptors_in);
	descriptor->compute(lib_patch, keypoints_lib, descriptors_lib);

	//feature matching
	vector<cv::DMatch> matches;
	matcher->match(descriptors_in, descriptors_lib, matches);
	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_in.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	//-- Use only "good" matches (i.e. whose distance is less than 3 )
	//vector< DMatch > sorted_matches;
	vector<cv::DMatch> temp;
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < matches.size() - 1; i++)
		{
			if (matches[i].distance > matches[i + 1].distance)
			{
				temp.push_back(matches[i]);
				matches.erase(matches.begin() + i);
				matches.insert(matches.begin() + i + 1, temp[0]);
				temp.pop_back();
				swapped = true;
			}
		}
	}
	std::vector<cv::DMatch> good_matches;
	for (int i = 0; i < 10; i++)
	{
		cout << matches[i].distance << endl;
		good_matches.push_back(matches[i]);
	}
	bool isFault;
	if (good_matches[9].distance > 4)
	{
		isFault = true;
		cout << "Error in vin punching" << endl;
		cout << "Error exceeds allowable margin by: " << good_matches[9].distance - 2 << endl;
	}
	else
	{
		isFault = false;
		cout << "Vin punching is ok" << endl;
	}
	//-- Draw matches
	cv::Mat img_matches;
	drawMatches(input_patch, keypoints_in, lib_patch, keypoints_lib, good_matches, img_matches, cv::Scalar::all(-1),
		cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//-- Show detected matches
	imshow("Good Matches", img_matches);
	return isFault;
}