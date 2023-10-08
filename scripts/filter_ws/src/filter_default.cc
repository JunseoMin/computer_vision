#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernal);

cv::Mat padding(cv::Mat input_mat,const int padding_size, const int select);
void zero_padding(const cv::Mat &input_mat, cv::Mat &padded_mat);
void repetition_padding(const cv::Mat &input_mat, cv::Mat &padded_mat);
void mirror_padding(const cv::Mat &input_mat, cv::Mat &padded_mat);

void filtering(cv::Mat padded_input,const std::vector<double> &kernal);

using namespace std;
using namespace cv;

int main(void){
    Mat color_img;
    Mat gray_img;
    Mat padded_color_zero;
    Mat padded_color_repetition;
    Mat padded_gray_mirror;

    vector<double> kernal;

    get_value(kernal);

    color_img=imread("/home/junseo/2023-2/computer_vision/images/kkang_tae.jpg");
    
    cvtColor(color_img, gray_img, COLOR_BGR2GRAY);

    padded_color_zero = padding(color_img, kernal.size() , 1);
    // padded_color_repetition = padding(color_img, kernal.size() / 2 , 2);
    // padded_gray_mirror = padding(gray_img, kernal.size() / 2 , 3);


    // filtering(padded_color_zero, kernal);
    // filtering(padded_color_repetition, kernal);
    // filtering(padded_gray_mirror, kernal);

    return 0;
}

void get_value(vector<double> &kernal) {
    int num = 1000;
    // cout << "Input kernel size: " << endl;
    // cin >> num;

    kernal.resize(2 * num + 1);

    cout << "Kernel size set: " << 2 * num + 1 << endl;
    cout << "Input " << 2 * num + 1 << " values for the kernel:" << endl;

    // for (int i = 0; i < 2 * num + 1; i++) {
    //     cin >> kernal[i];
    // }

    for (int i = 0; i < 2 * num + 1; i++) {
        kernal[i]=1;
    }

}


Mat padding(Mat input_mat,const int padding_size ,const int select){
    // select: 1 = zero_padding , 2 = repetition_padding , 3 = mirror_padding
    int height = input_mat.rows;
    int width = input_mat.cols;
    Mat padded_mat(width, height + padding_size - 1, input_mat.type());

    switch (select)
    {
    case 1:
        zero_padding( input_mat, padded_mat);
        break;
    
    case 2:
        repetition_padding(input_mat, padded_mat);
        break;

    case 3:
        mirror_padding(input_mat, padded_mat);
        break;

    default:
        cout<<"not selected"<<endl;
        break;
    }
    imshow("output image", padded_mat);
	waitKey(0);
    return padded_mat;
}

void zero_padding(const Mat &input_mat , Mat &padded_mat) {
    // fill padded data
    int origin_height = input_mat.rows;    
    int origin_width = input_mat.cols;
    int padded_height = padded_mat.rows;
    int padded_width = padded_mat.cols;

    int gap = (padded_height - origin_height)/2;

    for (int x = 0; x < padded_height; x++)
    {
        for (int y = 0; y < padded_width; y++)
        {
            // edge padding
            if ((0 <= x-gap)&&(x-gap < origin_height))
            {
                padded_mat.data[y*padded_width+x]=input_mat.data[y*origin_width+(x-gap)];
            }    
        }
        
        
    }

}

void repetition_padding(const cv::Mat &input_mat, cv::Mat &padded_mat) {

}

void mirror_padding(const cv::Mat &input_mat, cv::Mat &padded_mat) {

}

void filtering(Mat padded_input,const vector<double> &kernal) {
    
}