#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>

void get_value(std::vector<double> &kernel) {
    // Populate the kernel vector with arbitrary values
    kernel = {1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0};
}

void zero_padding(const cv::Mat &input_mat, cv::Mat &padded_mat, const int padding_size) {
    // Check if the input_mat and padded_mat have the same data type
    if (input_mat.type() != padded_mat.type()) {
        std::cerr << "Input and padded matrices must have the same data type." << std::endl;
        return;
    }

    int pad = padding_size / 2;  // Padding size on each side

    copyMakeBorder(input_mat, padded_mat, pad, pad, pad, pad, cv::BORDER_CONSTANT, cv::Scalar(0));
    cv::imshow("Padd", padded_mat);
    cv::waitKey(0);
}

void filtering(const cv::Mat &padded_input, const std::vector<double> &kernel) {
    cv::Mat output(padded_input.rows, padded_input.cols, padded_input.type());

    int kernel_size = static_cast<int>(sqrt(kernel.size()));
    int kCenterX = kernel_size / 2;
    int kCenterY = kernel_size / 2;

    for (int y = kCenterY; y < padded_input.rows - kCenterY; y++) {
        for (int x = kCenterX; x < padded_input.cols - kCenterX; x++) {
            double sum = 0.0;
            for (int ky = 0; ky < kernel_size; ky++) {
                for (int kx = 0; kx < kernel_size; kx++) {
                    int pixelX = x - kCenterX + kx;
                    int pixelY = y - kCenterY + ky;
                    double pixelValue = static_cast<double>(padded_input.at<uchar>(pixelY, pixelX));
                    double kernelValue = kernel[ky * kernel_size + kx];
                    sum += pixelValue * kernelValue;
                }
            }
            output.at<uchar>(y, x) = static_cast<uchar>(sum);
        }
    }

    cv::Mat filtered_image = output(cv::Rect(kCenterX, kCenterY, padded_input.cols - kernel_size, padded_input.rows - kernel_size));
    cv::imshow("Filtered Image", filtered_image);
    cv::waitKey(0);
}

using namespace std;
using namespace cv;

int main(void) {
    Mat color_img;
    Mat gray_img;
    vector<double> kernel;

    color_img = imread("/home/junseo/2023-2/computer_vision/images/Lena_256x256.png");
    waitKey(100);
    cvtColor(color_img, gray_img, COLOR_BGR2GRAY);

    get_value(kernel);

    Mat padded_gray_zero(gray_img.rows + (kernel.size() - 1), gray_img.cols + (kernel.size() - 1), gray_img.type());

    zero_padding(gray_img, padded_gray_zero, kernel.size());

    filtering(padded_gray_zero, kernel);

    return 0;
}
