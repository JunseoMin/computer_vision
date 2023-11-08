#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void generateNoise(const Mat& input, Mat& output, double dev, double mean);

int main (void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");
    
    Mat lowNoiseLena;
    Mat highNoiseLena;

    double lowNoiseStdDev = 10.0;
    double highNoiseStdDev = 50.0;

    generateNoise(lena512,lowNoiseLena, lowNoiseStdDev, 0.0);
    generateNoise(lena512,highNoiseLena, highNoiseStdDev, 0.0);

    // show image
    imshow("origin", lena512);
    imshow("low noise Lena", lowNoiseLena);
    imshow("high noise Lena", highNoiseLena);

    waitKey(0);

    return 0;
}

void generateNoise(const Mat& input, Mat& output, double dev, double mean){
    output = input.clone();
    Mat noise(input.size(), input.type());

    randn(noise, mean, dev);

    add(output, noise, output, Mat(), input.type());
}