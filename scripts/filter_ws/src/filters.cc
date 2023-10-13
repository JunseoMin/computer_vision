#include <opencv2/opencv.hpp>
using namespace cv;

Mat applyMovingAverage(const Mat& input);
Mat applyLaplacian(const Mat& input);
Mat applySharpening(const Mat& input, const Mat& laplacian);

int main() {
    Mat input_image = imread("/home/junseo/2023-2/computer_vision/images/Lena_256x256.png", IMREAD_GRAYSCALE);

    Mat moving_average_output = applyMovingAverage(input_image);
    imshow("Moving Average Output", moving_average_output);

    Mat laplacian_output = applyLaplacian(input_image);
    imshow("Laplacian Output", laplacian_output);

    Mat sharpened_output = applySharpening(input_image, laplacian_output);
    imshow("Sharpened Output", sharpened_output);

    waitKey(0);  // Wait for a key press before closing the windows

    return 0;
}

Mat applyMovingAverage(const Mat& input) {
    int rows = input.rows;
    int cols = input.cols;
    int filter_size = 3;

    Mat output(rows, cols, input.type());

    for (int y = 1; y < rows - 1; y++) {
        for (int x = 1; x < cols - 1; x++) {
            int sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int index = (y + i) * cols + (x + j);
                    sum += input.data[index];
                }
            }
            int output_index = y * cols + x;
            output.data[output_index] = sum / 9;
        }
    }

    return output;
}

Mat applyLaplacian(const Mat& input) {
    int rows = input.rows;
    int cols = input.cols;

    Mat output(rows, cols, input.type());

    for (int y = 1; y < rows - 1; y++) {
        for (int x = 1; x < cols - 1; x++) {
            int sum = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int index = (y + i) * cols + (x + j);
                    sum += input.data[index] * -1;
                }
            }
            int output_index = y * cols + x;
            sum += 8 * input.data[output_index];
            output.data[output_index] = sum;
        }
    }

    return output;
}

Mat applySharpening(const Mat& input, const Mat& laplacian) {
    int rows = input.rows;
    int cols = input.cols;

    Mat output(rows, cols, input.type());

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int input_index = y * cols + x;
            int laplacian_index = y * cols + x;
            int sum = input.data[input_index] + laplacian.data[laplacian_index];
            output.data[input_index] = saturate_cast<uchar>(sum);
        }
    }

    return output;
}
