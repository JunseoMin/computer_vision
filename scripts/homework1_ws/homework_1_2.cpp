// ubuntu 20.04
// gcc build
#define PI 3.141592

#include <iostream>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void rotation(double angle, Mat& img);

int main(void) {
    Mat img_in;
    Mat img_gray;

	img_in = imread("/home/junseo/2023-2/computer_vision/docs/hw1/Lena.png");
	cvtColor(img_in, img_gray, cv::COLOR_RGB2GRAY);

    rotation(30.0,img_gray);
    rotation(45.0,img_gray);
    rotation(60.0,img_gray);

	return 0;
    
}

void rotation(double angle, Mat& img)
{
    int col=img.cols;
    int row=img.rows;

    Mat rotated(row, col, img.type());

    double center_x = col/2.0;
    double center_y = row/2.0;

    double radian = angle * PI / 180.0;

    double rotated_x;
    double rotated_y;


    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            double rotated_x = cos(radian) * (x - center_x) - sin(radian) * (y - center_y) + center_x;
            double rotated_y = sin(radian) * (x - center_x) + cos(radian) * (y - center_y) + center_y;
            if (rotated_x >= 0 && rotated_x < col && rotated_y >= 0 && rotated_y < row)
            {
                rotated.data[y * col + x]=img.data[int(rotated_y) * col + int(rotated_x)];
            }
        }

    }
    
    imshow("output image", rotated);
	waitKey(0);

}