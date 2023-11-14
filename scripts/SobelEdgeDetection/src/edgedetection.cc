#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;
using namespace cv;

void sobel_edge_detect(const Mat& input, Mat& output, bool heading);

int main(void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");

    lena512.convertTo(lena512,CV_8U);
    cvtColor(lena512,lena512,COLOR_RGB2GRAY);   // convert color to gray

    Mat xSobel(lena512.rows, lena512.cols, lena512.type());
    Mat ySobel(lena512.rows, lena512.cols, lena512.type());

    sobel_edge_detect(lena512, xSobel, true);
    sobel_edge_detect(lena512, ySobel, false);

    Mat sobel_Edge;
    Mat sobel_Edge_high;

    sobel_edge_mask(xSobel, ySobel, sobel_Edge, 0); //sobel edge masking by threshold = ?
    sobel_edge_mask(xSobel, ySobel, sobel_Edge_high, 0); //sobel edge masking by threshold = ?(higher threashold than before)

    // !! use CV function to apply gaussian filter !!
    Mat gaussian_filtered_lena;
    Mat gaussian_filtered_lena_high;

    Mat filtered_sobel;
    Mat filtered_sobel_high;

    Mat x;
    Mat y;

    sobel_edge_detect(gaussian_filtered_lena, x, true);    //x
    sobel_edge_detect(gaussian_filtered_lena, y, false);    //y

    sobel_edge_mask(x, y, filtered_sobel, 0);
    
    sobel_edge_detect(gaussian_filtered_lena_high, x, true);    //x
    sobel_edge_detect(gaussian_filtered_lena_high, y, false);    //y
    
    sobel_edge_mask(x, y, filtered_sobel_high, 0);
    
    //imshows
    imshow("gx image", xSobel);
    imshow("gy image", ySobel);
    imshow("low threshold", sobel_Edge);
    imshow("high threshold", sobel_Edge_high);
    imshow("low sigma", filtered_sobel);
    imshow("high sigma", filtered_sobel_high);


    return 0;
}


void sobel_edge_detect(const Mat& input, Mat& output, bool heading){  // true --> gx, false --> gy
    // apply sobel mask to output by heading x or y axis

}

void sobel_edge_mask(const Mat& x_image, const Mat& y_image, Mat& output, const size_t _Threshold){
    // add sobel x and sobel y

}
