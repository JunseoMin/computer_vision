#include <iostream>

#include <math.h>

#include <opencv/cv2.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void){
    Mat img_in;

	img_in = imread("Lena.png");
	cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
	imshow("source img", img_in);


    return 0;
}