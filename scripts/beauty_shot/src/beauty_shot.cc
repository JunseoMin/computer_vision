#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
//cv_8uc3 
using namespace cv;
using namespace std;

void get_sliced(const Mat& origin,Mat& slicde);

int main()
{
    Mat origin_img;    
    origin_img = imread("../../../images/hw_3_img/bf_img.jpeg");
    
    Mat sliced_img(origin_img.rows,origin_img.cols,origin_img.type());
    // cout<<origin_img.type();
    // cout<<origin_img.cols;

    // check load image
    // imshow("sliced img",sliced_img);
    // waitKey(0);
    get_sliced(origin_img,sliced_img);
    
    imshow("sliced img",sliced_img);
    waitKey(0);


    return 0;
}


void get_sliced(const Mat& origin, Mat& slicde) {
    unsigned char min_r = 0;
    unsigned char max_r = 255;
    unsigned char min_g = 0;
    unsigned char max_g = 255;
    unsigned char min_b = 0;
    unsigned char max_b = 255;

    for (int x = 0; x < origin.cols; x++) {
        for (int y = 0; y < origin.rows; y++) {
            int idx = y * origin.cols * 3 + x * 3;

            unsigned char pixel_b = origin.data[idx];
            unsigned char pixel_g = origin.data[idx + 1];
            unsigned char pixel_r = origin.data[idx + 2];

            if ((min_b < pixel_b && pixel_b < max_b) ||
                (min_g < pixel_g && pixel_g < max_g) ||
                (min_r < pixel_r && pixel_r < max_r)) {
                slicde.data[idx] = pixel_b;
                slicde.data[idx + 1] = pixel_g;
                slicde.data[idx + 2] = pixel_r;
            } else {
                slicde.data[idx] = 3;  // B
                slicde.data[idx + 1] = 3;  // G
                slicde.data[idx + 2] = 3;  // R
            }
        }
    }
}
