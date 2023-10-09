#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernal);

cv::Mat padding(cv::Mat input_mat,const int padding_size, const int select);
void zero_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size);
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
    padded_color_repetition = padding(color_img, kernal.size() / 2 , 2);
    padded_gray_mirror = padding(gray_img, kernal.size() / 2 , 3);


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


Mat padding(Mat input_mat,const int padding_size ,const int select){
    // select: 1 = zero_padding , 2 = repetition_padding , 3 = mirror_padding
    int height = input_mat.rows;
    int width = input_mat.cols;
    Mat padded_mat(width, height + padding_size - 1, input_mat.type());

    switch (select)
    {
    case 1:
        zero_padding( input_mat, padded_mat, padding_size);
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

    return padded_mat;
}

void zero_padding(const Mat &input_mat , Mat &padded_mat, const int padding_size) {
    // Fill padded data with zeros
    int height = input_mat.rows;
    int width = input_mat.cols;
    int padded_height = padded_mat.rows;
    int padded_width = padded_mat.cols;

    for (int y = 0; y < padded_height; y++) {
        for (int x = 0; x < padded_width; x++) {
            if (y < padding_size || y >= height + padding_size || x < padding_size || x >= width + padding_size) {
                for (int c = 0; c < input_mat.channels(); c++) {
                    padded_mat.data[y * padded_mat.step + x * padded_mat.elemSize() + c] = 0;
                }
            } else {
                for (int c = 0; c < input_mat.channels(); c++) {
                    int original_x = x - padding_size;
                    int original_y = y - padding_size;
                    padded_mat.data[y * padded_mat.step + x * padded_mat.elemSize() + c] = input_mat.data[original_y * input_mat.step + original_x * input_mat.elemSize() + c];
                }
            }
        }
    }
}

void repetition_padding(const cv::Mat &input_mat, cv::Mat &padded_mat) {
    int height = input_mat.rows;
    int width = input_mat.cols;
    int padded_height = padded_mat.rows;
    int padded_width = padded_mat.cols;

    for (int y = 0; y < padded_height; y++) {
        for (int x = 0; x < padded_width; x++) {
            int original_x = x % width;
            int original_y = y % height;

            for (int c = 0; c < input_mat.channels(); c++) {
                padded_mat.data[y * padded_mat.step + x * padded_mat.elemSize() + c] = input_mat.data[original_y * input_mat.step + original_x * input_mat.elemSize() + c];
            }
        }
    }
}

void mirror_padding(const cv::Mat &input_mat, cv::Mat &padded_mat) {
    int height = input_mat.rows;
    int width = input_mat.cols;
    int padded_height = padded_mat.rows;
    int padded_width = padded_mat.cols;

    for (int y = 0; y < padded_height; y++) {
        for (int x = 0; x < padded_width; x++) {
            int original_x = std::min(std::max(x, 0), width - 1);
            int original_y = std::min(std::max(y, 0), height - 1);

            for (int c = 0; c < input_mat.channels(); c++) {
                padded_mat.data[y * padded_mat.step + x * padded_mat.elemSize() + c] = input_mat.data[original_y * input_mat.step + original_x * input_mat.elemSize() + c];
            }
        }
    }
}

void filtering(cv::Mat padded_input, const vector<double> &kernal) {
    int kernel_size = kernal.size();
    int height = padded_input.rows;
    int width = padded_input.cols;

    cv::Mat output_image = cv::Mat::zeros(height, width, padded_input.type());

    int kernel_half = kernel_size / 2;

    for (int y = kernel_half; y < height - kernel_half; y++) {
        for (int x = kernel_half; x < width - kernel_half; x++) {
            double sum = 0.0;

            for (int i = -kernel_half; i <= kernel_half; i++) {
                for (int j = -kernel_half; j <= kernel_half; j++) {
                    for (int c = 0; c < padded_input.channels(); c++) {
                        sum += kernal[i + kernel_half] * kernal[j + kernel_half] * padded_input.data[(y + i) * padded_input.step + (x + j) * padded_input.elemSize() + c];
                    }
                }
            }

            for (int c = 0; c < padded_input.channels(); c++) {
                output_image.data[y * output_image.step + x * output_image.elemSize() + c] = static_cast<uchar>(sum);
            }
        }
    }
    imshow("output image", output_image);
	waitKey(0);
}