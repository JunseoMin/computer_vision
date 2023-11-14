#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;
using namespace cv;

void sobel_edge_mask(const Mat& input, Mat& output, bool heading);

int main(void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");

    lena512.convertTo(lena512,CV_8U);
    cvtColor(lena512,lena512,COLOR_RGB2GRAY);   // convert color to gray

    Mat xSobel(lena512.rows, lena512.cols, lena512.type());
    Mat ySobel(lena512.rows, lena512.cols, lena512.type());

    sobel_edge_mask(lena512, xSobel, true);
    sobel_edge_mask(lena512, ySobel, true);

    
    return 0;
}


void sobel_edge_mask(const Mat& input, Mat& output, bool heading){  // true --> gx, false --> gy
    
    if (heading)
    {
        int x = input.rows;
        int y = input.cols;
    }
    else{
        int x = input.rows;
        int y = input.cols;
    }
    
}
