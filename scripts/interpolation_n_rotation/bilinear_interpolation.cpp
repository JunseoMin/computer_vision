// ubuntu 20.04
// gcc build

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void bilinear_interpolation(int x_size,int y_size ,Mat& img);

int main(void) {
    Mat img_in;
    Mat img_gray;

    img_in = imread("/home/junseo/2023-2/computer_vision/images/Lena_256x256.png");
    
    if (img_in.empty()) {
        cerr << "Image not found!" << endl;
        return -1;
    }

    cvtColor(img_in, img_gray, COLOR_BGR2GRAY);
    imshow("source img", img_gray);
    waitKey(0);

    bilinear_interpolation(436,436,img_gray);
    bilinear_interpolation(512,512,img_gray);


    return 0;
}

void bilinear_interpolation(int x_size,int y_size,Mat& img)
{
    int col = img.cols;
    int row = img.rows;

    Mat interpolated(y_size, x_size, img.type());

    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            float src_x = x * (float(col) / x_size);
            float src_y = y * (float(row) / y_size);

            int x0 = int(src_x);
            int x1 = x0 + 1;
            int y0 = int(src_y);
            int y1 = y0 + 1;

            if (x1 >= col) x1 = x0;
            if (y1 >= row) y1 = y0;

            float dx = src_x - x0;
            float dy = src_y - y0;

            unsigned char pixel00 = img.data[y0*col + x0];
            unsigned char pixel01 = img.data[y0*col + x1];
            unsigned char pixel10 = img.data[y1*col + x0];
            unsigned char pixel11 = img.data[y1*col + x1];

            float interpolated_value = float(pixel00) * (1 - dx) * (1 - dy) +
                                       float(pixel01) * dx * (1 - dy) +
                                       float(pixel10) * (1 - dx) * dy +
                                       float(pixel11) * dx * dy;

            interpolated.data[y*y_size + x] = static_cast<unsigned char>(interpolated_value);
        }
    }

    imshow("Interpolated Image", interpolated);
    waitKey(0);
}