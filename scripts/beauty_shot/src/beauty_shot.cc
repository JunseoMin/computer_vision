#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
//cv_8uc3 
using namespace cv;
using namespace std;

void get_sliced(const Mat& origin,Mat& sliced);
void make_beauty(const Mat& origin,Mat& sliced);
void MAF(Mat& map);


int main()
{
    Mat origin_img;    
    origin_img = imread("../../../images/hw_3_img/bf_img.jpeg");
    
    Mat sliced_img(origin_img.rows,origin_img.cols,origin_img.type());
    get_sliced(origin_img,sliced_img);
    make_beauty(origin_img,sliced_img);
    imshow("filtered img",sliced_img);
    waitKey(0);


    return 0;
}


void get_sliced(const Mat& origin, Mat& sliced) {
    
    unsigned char min_r = 160;
    unsigned char max_r = 225;
    unsigned char min_g = 120;
    unsigned char max_g = 195;
    unsigned char min_b = 90;
    unsigned char max_b = 190;

    for (int x = 0; x < origin.cols; x++) {
        for (int y = 0; y < origin.rows; y++) {
            int idx = y * origin.cols * 3 + x * 3;

            unsigned char pixel_b = origin.data[idx];
            unsigned char pixel_g = origin.data[idx + 1];
            unsigned char pixel_r = origin.data[idx + 2];

            if ((min_b < pixel_b && pixel_b < max_b) &&
                (min_g < pixel_g && pixel_g < max_g) &&
                (min_r < pixel_r && pixel_r < max_r)) {
                sliced.data[idx] = 255;
                sliced.data[idx + 1] = 255;
                sliced.data[idx + 2] = 255;
            } else {
                sliced.data[idx] = 0;  // B
                sliced.data[idx + 1] = 0;  // G
                sliced.data[idx + 2] = 0;  // R
            }
        }
    }
}

void make_beauty(const Mat& origin,Mat& sliced){
    Mat padding(origin.rows,origin.cols,origin.type());

    for (int x = 0; x < origin.cols; x++) {
        for (int y = 0; y < origin.rows; y++) {
            
            int idx = y * origin.cols * 3 + x * 3;
            unsigned char pixel_b = sliced.data[idx];
            unsigned char pixel_g = sliced.data[idx + 1];
            unsigned char pixel_r = sliced.data[idx + 2];

            if (sliced.data[idx] != 255){ //not the face
                sliced.data[idx] = origin.data[idx];    // b
                sliced.data[idx+1] = origin.data[idx+1];    // g
                sliced.data[idx+2] = origin.data[idx+2];    // r
            }
            else{   //face (255) filter
                
                int b_sum = 0;
                int g_sum = 0;
                int r_sum = 0;
                
                for (int i = -1; i < 1; i++)
                {
                    for (int j = -1; j < 1; j++)
                    {
                        int f_idx = (y+3*i) * origin.cols * 3 + (x+3*j) * 3;
                        b_sum += origin.data[f_idx];
                        g_sum += origin.data[f_idx+1];
                        r_sum += origin.data[f_idx+2];
                    }                    
                }
                sliced.data[idx] = b_sum/9;
                sliced.data[idx+1] = g_sum/9;
                sliced.data[idx+2] = r_sum/9;
            }
        }
    }

    cout<<"finished";
}