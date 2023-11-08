#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void generateGaussianNoise(const Mat& input, Mat& output, double dev, double mean);
void generateSaltPepperNoise(const Mat& input, Mat& output, double percentage);

void median_filter(const Mat& input, Mat& output);
void mean_filter(const Mat& input, Mat& output);

int main (void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");
    
    //gaussian
    Mat lowGaussian_NoiseLena;
    Mat highGaussian_NoiseLena;

    double lowNoiseStdDev = 10.0;
    double highNoiseStdDev = 50.0;

    generateGaussianNoise(lena512,lowGaussian_NoiseLena, lowNoiseStdDev, 0.0);
    generateGaussianNoise(lena512,highGaussian_NoiseLena, highNoiseStdDev, 0.0);
    
    //slat pepper
    Mat saltpepperlow;
    Mat saltpepperhigh;

    generateSaltPepperNoise(lena512,saltpepperlow,0.05);
    generateSaltPepperNoise(lena512,saltpepperhigh,0.1);

    // show noised image
    imshow("origin", lena512);
    imshow("low noise Lena", lowGaussian_NoiseLena);
    imshow("high noise Lena", highGaussian_NoiseLena);
    imshow("saltpapper 0.05", saltpepperlow);
    imshow("saltpapper 0.1", saltpepperhigh);

    //filtering
    Mat filtered_mean_h_gaussian;
    Mat filtered_med_h_gaussian;
    Mat filtered_mean_l_gaussian;
    Mat filtered_med_l_gaussian;

    Mat filtered_mean_l_sp;
    Mat filtered_med_l_sp;
    Mat filtered_mean_h_sp;
    Mat filtered_med_h_sp;

    mean_filter(lowGaussian_NoiseLena,filtered_mean_l_gaussian);
    mean_filter(highGaussian_NoiseLena,filtered_mean_h_gaussian);
    mean_filter(saltpepperlow,filtered_mean_l_sp);
    mean_filter(saltpepperhigh,filtered_mean_h_sp);


    median_filter(lowGaussian_NoiseLena, filtered_med_l_gaussian);
    median_filter(highGaussian_NoiseLena, filtered_med_h_gaussian);
    median_filter(saltpepperlow, filtered_med_l_sp);
    median_filter(saltpepperhigh, filtered_med_h_sp);

    imshow("high gaussian mean filtered", filtered_mean_h_gaussian);
    imshow("low gaussian mean filtered", filtered_mean_l_gaussian);
    imshow("high salt&peppper mean filtered", filtered_mean_h_sp);
    imshow("low salt&peppper mean filtered", filtered_mean_l_sp);

    imshow("high gaussian median filtered", filtered_med_h_gaussian);
    imshow("low gaussian median filtered", filtered_med_l_gaussian);
    imshow("high salt&peppper median filtered", filtered_med_h_sp);
    imshow("low salt&peppper median filtered", filtered_med_l_sp);

    waitKey(0);

    return 0;
}

void generateGaussianNoise(const Mat& input, Mat& output, double dev, double mean){
    output = input.clone();
    Mat noise(input.size(), input.type());

    randn(noise, mean, dev);

    add(output, noise, output, Mat(), input.type());
    for (int x = 0; x < input.rows; x++)
    {
        for (int y = 0; y < input.cols; y++)
        {
            for (int c = 0; c < input.channels(); c++)
            {
                int added = output.at<Vec3b>(y,x)[c] + noise.at<Vec3b>(y,x)[c];
                added = max(0,min(255,added));
                output.at<Vec3b>(y,x)[c] = static_cast<uchar>(added);
            }
        }
    }
}

void generateSaltPepperNoise(const Mat& input, Mat& output, double percentage){
    output = input.clone();

    int num_saltNpepper = static_cast<int>(input.total()*percentage/2);
    for (int i = 0; i < num_saltNpepper; i++)
    {
        int x = rand()%input.rows;
        int y = rand()%input.cols;
        int channel = rand() % input.channels();

        if (rand()%2==0)
        {
            output.at<Vec3d>(x,y)[channel] = 0;    //salt
        }
        else output.at<Vec3d>(x,y)[channel] = 255;     //pepper
    }
}

void median_filter(const Mat& input, Mat& output){
    //3x3 median filter
    
}

void mean_filter(const Mat& input, Mat& output){
    //3x3 mean filter

}
