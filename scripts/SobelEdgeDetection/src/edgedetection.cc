#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;
using namespace cv;

void sobel_edge_detect(const Mat& input, Mat& output, bool heading);
void sobel_edge_mask(const Mat& x_image, const Mat& y_image, Mat& output, const int _Threshold);

int main(void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");

    lena512.convertTo(lena512,CV_8U);
    cvtColor(lena512,lena512,COLOR_RGB2GRAY);   // convert color to gray

    Mat xSobel(lena512.rows, lena512.cols, lena512.type());
    Mat ySobel(lena512.rows, lena512.cols, lena512.type());

    sobel_edge_detect(lena512, xSobel, true);
    sobel_edge_detect(lena512, ySobel, false);

    Mat sobel_Edge(lena512.rows, lena512.cols, lena512.type());

    Mat sobel_Edge_low(lena512.rows, lena512.cols, lena512.type());
    Mat sobel_Edge_high(lena512.rows, lena512.cols, lena512.type());

    sobel_edge_mask(xSobel, ySobel, sobel_Edge, 0); //sobel edge(gx + gy)

    sobel_edge_mask(xSobel, ySobel, sobel_Edge_low, 30); //sobel edge masking by low threshold = ?
    sobel_edge_mask(xSobel, ySobel, sobel_Edge_high, 100); //sobel edge masking by high threshold = ?(higher threashold than before)

    // // !! use CV function to apply gaussian filter !!
    Mat gaussian_filtered_lena;
    Mat gaussian_filtered_lena_high;
    GaussianBlur(lena512, gaussian_filtered_lena, Size(5, 5), 1.5);
    GaussianBlur(lena512, gaussian_filtered_lena_high, Size(5, 5), 3.);

    Mat filtered_sobel(lena512.rows, lena512.cols, lena512.type());
    Mat filtered_sobel_high(lena512.rows, lena512.cols, lena512.type());

    Mat x(lena512.rows, lena512.cols, lena512.type());
    Mat y(lena512.rows, lena512.cols, lena512.type());

    sobel_edge_detect(gaussian_filtered_lena, x, true);    //x
    sobel_edge_detect(gaussian_filtered_lena, y, false);    //y

    sobel_edge_mask(x, y, filtered_sobel, 100);
    
    sobel_edge_detect(gaussian_filtered_lena_high, x, true);    //x
    sobel_edge_detect(gaussian_filtered_lena_high, y, false);    //y
    
    sobel_edge_mask(x, y, filtered_sobel_high, 100);
    
    //imshows
    imshow("gx image", xSobel);
    imshow("gy image", ySobel);
    imshow("without threshold image", sobel_Edge);

    imshow("low threshold", sobel_Edge_low);
    imshow("high threshold", sobel_Edge_high);
    
    imshow("low sigma", filtered_sobel);
    imshow("high sigma", filtered_sobel_high);

    waitKey(0);
    return 0;
}


void sobel_edge_detect(const Mat& input, Mat& output, bool heading){  // true --> gx, false --> gy
    // apply sobel mask to output by heading x or y axis
    Mat sobelKernel;
    if (heading) {
        sobelKernel = (Mat_<int>(3, 3) << -1, 0, 1, 
                                          -2, 0, 2,
                                          -1, 0, 1);
    } else {
        sobelKernel = (Mat_<int>(3, 3) << -1, -2, -1,
                                           0, 0, 0, 
                                           1, 2, 1);
    }


    for (int i = 1; i < input.rows - 1; ++i) {
        for (int j = 1; j < input.cols - 1; ++j) {
            int sum = 0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    sum += input.at<uchar>(i + k, j + l) * sobelKernel.at<int>(1 + k, 1 + l);
                }
            }
            output.at<uchar>(i, j) = static_cast<uchar> (max(0,min(sum,255)));
        }
    }

}

void sobel_edge_mask(const Mat& x_image, const Mat& y_image, Mat& output, const int _Threshold){
    // add sobel x and sobel y
    
    for (int i = 0; i < x_image.rows; ++i) {
        for (int j = 0; j < x_image.cols; ++j) {
            uchar magnitude = static_cast<uchar>(x_image.at<uchar>(i, j) + y_image.at<uchar>(i, j));
            output.at<uchar>(i, j) = min(255, (magnitude > _Threshold) ? magnitude : 0);
        }
    }

}
