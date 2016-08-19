#include <iostream>
#include "ORBextractor.h"


int main(int *argc, char *argv[])
{
	ORBextractor orb(2000, 1.2, 1, 20, 1);
	cv::Mat descriptor;
	std::vector<cv::KeyPoint> keypoints;
	
	cv::Mat img1 = cv::imread("match_3_first.jpg");
	cv::Mat img2 = cv::imread("match_3_second.jpg");

	cv::Mat img1_grey, img2_grey;
	cv::cvtColor(img1, img1_grey, cv::COLOR_BGR2GRAY);
	cv::cvtColor(img2, img2_grey, cv::COLOR_BGR2GRAY);

	orb(img1_grey, cv::Mat(), keypoints, descriptor);
	cv::drawKeypoints(img1, keypoints, img1, cv::Scalar::all(-1));
	cv::imwrite("match_3_first_keypoints.jpg", img1);

	orb(img2_grey, cv::Mat(), keypoints, descriptor);
	cv::drawKeypoints(img2, keypoints, img2, cv::Scalar::all(-1));
	cv::imwrite("match_3_second_keypoints.jpg", img2);

	return 1;
}