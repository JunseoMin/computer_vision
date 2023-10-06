#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernal);

cv::Mat padding(cv::Mat input_mat, int padding_size, int select);
void zero_padding(cv::Mat &input_mat, int padding_size);
void repetition_padding(cv::Mat &input_mat, int padding_size);
void mirror_padding(cv::Mat &input_mat, int padding_size);

void filtering(cv::Mat padded_input, std::vector<double> &kernal);

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
    padded_color_repetition = padding(color_img, kernal.size() , 2);
    padded_gray_mirror = padding(gray_img, kernal.size() , 3);


    filtering(padded_color_zero, kernal);
    filtering(padded_color_repetition, kernal);
    filtering(padded_gray_mirror, kernal);

    return 0;
}

void get_value(vector<double> &kernal) {
    int num;
    cout << "Input kernel size: " << endl;
    cin >> num;

    kernal.resize(2 * num + 1);

    cout << "Kernel size set: " << 2 * num + 1 << endl;
    cout << "Input " << 2 * num + 1 << " values for the kernel:" << endl;

    for (int i = 0; i < 2 * num + 1; i++) {
        cin >> kernal[i];
    }
}


Mat padding(Mat input_mat,int padding_size ,int select){
    // select: 1 = zero_padding , 2 = repetition_padding , 3 = mirror_padding
    Mat padded_mat = input_mat.clone();

    switch (select)
    {
    case 1:
        zero_padding(padded_mat, padding_size);
        break;
    
    case 2:
        repetition_padding(padded_mat, padding_size);
        break;

    case 3:
        mirror_padding(padded_mat, padding_size);
        break;

    default:
        cout<<"not selected"<<endl;
        break;
    }
    return padded_mat;

}

void zero_padding(Mat &input_mat, int padding_size) {

}

void repetition_padding(Mat &input_mat, int padding_size) {

}

void mirror_padding(Mat &input_mat, int padding_size) {

}

void filtering(Mat padded_input, vector<double> &kernal) {
    
}