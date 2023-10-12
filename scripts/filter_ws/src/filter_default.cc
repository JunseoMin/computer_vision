#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernal);

void zero_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);
void repetition_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);
void mirror_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);

void filtering(const cv::Mat &padded_input,const std::vector<double> &kernal);

using namespace std;
using namespace cv;

int main(void){
    Mat color_img;
    Mat gray_img;
    vector<double> kernal;

    color_img=imread("/home/junseo/2023-2/computer_vision/images/Lena_256x256.png");
    // imshow("o Image", color_img);
    waitKey(100);    
    cvtColor(color_img, gray_img, COLOR_BGR2GRAY);
    
    get_value(kernal);   

    Mat padded_color_zero(color_img.rows,color_img.cols+(kernal.size()-1),gray_img.type());
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
    int width = padded_mat.cols;
    int heigth = padded_mat.rows;
    int in_w = input_mat.cols;
    int in_h = input_mat.rows;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < heigth; y++)
        {   
            int padded_index = y * width + x;
            int origin_index = y * in_w + x - (padding_size - 1) / 2;

            if (x - ((padding_size - 1) / 2) >= 0 && x < in_w) { 
                    padded_mat.data[padded_index] = input_mat.data[origin_index];
                }
            else
            {
                padded_mat.data[padded_index]=0;
            }
            
        }        
    }

    imshow("P Image", padded_mat);
    waitKey(0);
}

void repetition_padding(const Mat &input_mat, Mat &padded_mat, const int padding_size) {
    for (int x = 0; x < padded_mat.cols; x++) {
        for (int y = 0; y < padded_mat.rows; y++) {
            int padded_index = y * padded_mat.cols + x;
            int input_x = std::max(0, std::min(x - (padding_size - 1) / 2, input_mat.cols - 1));
            int input_y = std::max(0, std::min(y - (padding_size - 1) / 2, input_mat.rows - 1));
            int input_index = input_y * input_mat.cols + input_x;
            padded_mat.data[padded_index] = input_mat.data[input_index];
        }
    }
    imshow("P Image2", padded_mat);
    waitKey(100);
}

void filtering(const Mat &padded_input, const vector<double> &kernel) {
    Mat output_image = padded_input.clone(); // Initialize the output image with the same size as the padded input

    int kernel_size = kernel.size();
    int half_kernel_size = kernel_size / 2;

    for (int x = half_kernel_size; x < padded_input.cols - half_kernel_size; x++) {
        for (int y = half_kernel_size; y < padded_input.rows - half_kernel_size; y++) {
            double sum = 0.0;
            for (int i = -half_kernel_size; i <= half_kernel_size; i++) {
                for (int j = -half_kernel_size; j <= half_kernel_size; j++) {
                    int padded_index = (y + i) * padded_input.cols + (x + j);
                    double pixel_value = static_cast<double>(padded_input.data[padded_index]);
                    double kernel_value = kernel[i + half_kernel_size] * kernel[j + half_kernel_size];
                    sum += pixel_value * kernel_value;
                }
            }
            int output_index = y * output_image.cols + x;
            output_image.data[output_index] = static_cast<uchar>(sum);
        }
    }

    imshow("Filtered Image", output_image);
    waitKey(0);
}