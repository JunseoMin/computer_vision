#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernal);

void zero_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);
void repetition_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);
void mirror_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);

void filtering(cv::Mat padded_input,const std::vector<double> &kernal);

using namespace std;
using namespace cv;

int main(void){
    Mat color_img;
    Mat gray_img;
    vector<double> kernal;

    color_img=imread("/home/junseo/2023-2/computer_vision/images/kkang_tae.jpg");    
    cvtColor(color_img, gray_img, COLOR_BGR2GRAY);
    
    get_value(kernal);

    Mat padded_color_zero(gray_img.rows,gray_img.cols+(kernal.size()-1),gray_img.type());
    Mat padded_gray_repetition(gray_img.rows,gray_img.cols+(kernal.size()-1),gray_img.type());

    zero_padding(color_img, padded_color_zero , kernal.size());
    repetition_padding(color_img, padded_gray_repetition, kernal.size());


    filtering(padded_color_zero, kernal);
    filtering(padded_gray_repetition, kernal);

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
// y*padded_mat.cols + x = > data index
void zero_padding(const Mat &input_mat , Mat &padded_mat, const int padding_size) {
    // set input mat in the middle
    for (int x = 0; x < padded_mat.cols; x++)
    {
        for (int y = 0; y < padded_mat.rows; y++)
        {   
            int padded_index = y*padded_mat.cols + x;
            int input_index = y*input_mat.cols+x;
            
            if (padded_index - (padding_size - 1)/2 == input_index ){
                padded_mat.data[padded_index] = input_mat.data[input_index];
            }
        }        
    }
}

void repetition_padding(const Mat &input_mat, Mat &padded_mat, const int padding_size) {
    
    for (int x = 0; x < padded_mat.cols; x++)
    {
        for (int y = 0; y < padded_mat.rows; y++)
        {   
            int padded_index = y*padded_mat.cols + x;
            int input_index = y*input_mat.cols+x;
            
            if (padded_index - (padding_size - 1)/2 == input_index ){
                padded_mat.data[padded_index] = input_mat.data[input_index];
            }
            else
            {
                padded_mat.data[padded_index]=input_mat.data[input_index+(padding_size-1)/2];            
            }
        }        
    }
}

void filtering(Mat padded_input, const vector<double> &kernal, bool if_gray) {
    
    
    
    
    
    
    
    
    // int kernel_size = kernal.size();
    // int height = padded_input.rows;
    // int width = padded_input.cols;

    // Mat output_image = Mat::zeros(height, width, padded_input.type());

    // int kernel_half = kernel_size / 2;

    // for (int y = kernel_half; y < height - kernel_half; y++) {
    //     for (int x = kernel_half; x < width - kernel_half; x++) {
    //         double sum = 0.0;

    //         for (int i = -kernel_half; i <= kernel_half; i++) {
    //             for (int j = -kernel_half; j <= kernel_half; j++) {
    //                 sum += kernal[i + kernel_half] * kernal[j + kernel_half] * padded_input.data[(y + i) * padded_input.step + (x + j) * padded_input.elemSize()];
                    
    //                 for (int c = 0; c < 3; c++) {
    //                     sum += kernal[i + kernel_half] * kernal[j + kernel_half] * padded_input.data[(y + i) * padded_input.step + (x + j) * padded_input.elemSize() + c];
    //                 }
    //             }
    //         }

    //         for (int c = 0; c < 3; c++) {
    //             output_image.data[y * output_image.step + x * output_image.elemSize() + c] = static_cast<uchar>(sum);
    //         }
    //     }
    // }
    imshow("output image", output_image);
	waitKey(0);
}