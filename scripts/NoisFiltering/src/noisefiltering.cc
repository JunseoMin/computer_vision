#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void generateGaussianNoise(const Mat& input, Mat& output, const double dev, double mean);
void generateSaltPepperNoise(const Mat& input, Mat& output, const double percentage);

void median_filter(const Mat& input, Mat& output, const int filter_axis_len);
void mean_filter(const Mat& input, Mat& output, const int filter_axis_len);

int main (void){
    Mat lena512;
    lena512 = imread("/home/junseo/2023-2/computer_vision/images/lena_512x512.png");
    // cout<<lena512.type();
    lena512.convertTo(lena512,CV_8U);
    
    //gaussian
    Mat lowGaussian_NoiseLena = lena512.clone();
    Mat highGaussian_NoiseLena = lena512.clone();
    Mat saltpepperlow = lena512.clone();
    Mat saltpepperhigh = lena512.clone();

    double lowNoiseStdDev = 10.0;
    double highNoiseStdDev = 50.0;

    generateGaussianNoise(lena512, lowGaussian_NoiseLena, lowNoiseStdDev, 0.0);
    generateGaussianNoise(lena512, highGaussian_NoiseLena, highNoiseStdDev, 0.0);
    
    //slat pepper

    generateSaltPepperNoise(lena512,saltpepperlow,0.05);
    generateSaltPepperNoise(lena512,saltpepperhigh,0.1);

    // show noised image
    // imshow("origin", lena512);
    // imshow("low noise Lena", lowGaussian_NoiseLena);
    // imshow("high noise Lena", highGaussian_NoiseLena);
    // imshow("saltpapper 0.05", saltpepperlow);
    // imshow("saltpapper 0.1", saltpepperhigh);

    //filtering
    Mat filtered_mean_h_gaussian(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_med_h_gaussian(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_mean_l_gaussian(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_med_l_gaussian(lena512.rows,lena512.cols,lena512.type());

    Mat filtered_mean_l_sp(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_med_l_sp(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_mean_h_sp(lena512.rows,lena512.cols,lena512.type());
    Mat filtered_med_h_sp(lena512.rows,lena512.cols,lena512.type());

    mean_filter(lowGaussian_NoiseLena,filtered_mean_l_gaussian, 3);
    mean_filter(highGaussian_NoiseLena,filtered_mean_h_gaussian, 3);
    mean_filter(saltpepperlow,filtered_mean_l_sp, 3);
    mean_filter(saltpepperhigh,filtered_mean_h_sp, 3);

    median_filter(lowGaussian_NoiseLena, filtered_med_l_gaussian, 3);
    median_filter(highGaussian_NoiseLena, filtered_med_h_gaussian, 3);
    median_filter(saltpepperlow, filtered_med_l_sp, 3);
    median_filter(saltpepperhigh, filtered_med_h_sp, 3);

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

void generateGaussianNoise(const Mat& input, Mat& output, const double dev, double mean){
    Mat noise(input.size(), input.type());

    randn(noise, mean, dev);

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


void generateSaltPepperNoise(const Mat& input, Mat& output, const double percentage) {

    int num_saltNpepper = static_cast<int>(input.total() * percentage);
    for (int i = 0; i < num_saltNpepper; i++) {
        int x = rand() % input.rows;
        int y = rand() % input.cols;
        int randval = rand();

        for (int c = 0; c < input.channels(); c++) {
            if (randval%2) {
                output.at<Vec3b>(x, y)[c] = 255;  // salt
            } else {
                output.at<Vec3b>(x, y)[c] = 0;    // pepper
            }
        }
    }
}

void median_filter(const Mat& input, Mat& output, const int filter_axis_len){
    //3x3 median filter
    //zero padded
    int filter_size = (filter_axis_len - 1) / 2;
    int med_idx = (filter_axis_len*filter_axis_len+1)/2;

    for (int x = 0; x < input.rows; x++)
    {
        for (int y = 0; y < input.cols; y++)
        {
            for (int c = 0; c < input.channels(); c++)
            {
                int median = 0;
                vector<int> pixels;

                for (int i = -filter_size; i <= filter_size; i++) {
                    for (int j = -filter_size; j <= filter_size; j++) {
                
                        int _x = x + i;
                        int _y = y + j;

                        if (_x >= 0 && _x < input.rows && _y >= 0 && _y < input.cols) {
                            pixels.push_back(input.at<Vec3b>(_x,_y)[c]);
                        }
                    }
                }
                
                sort(pixels.begin(),pixels.end());
                output.at<Vec3b>(x,y)[c] = pixels[med_idx];
            }
            
        }
    }
}

void mean_filter(const Mat& input, Mat& output, const int filter_axis_len) {
    // zero padded
    int filter_size = (filter_axis_len - 1) / 2;

    for (int x = 0; x < input.rows; x++) {
        for (int y = 0; y < input.cols; y++) {
            for (int c = 0; c < input.channels(); c++) {
                int sum = 0;
                int cnt = 0;

                for (int i = -filter_size; i <= filter_size; i++) {
                    for (int j = -filter_size; j <= filter_size; j++) {
                        int _x = x + i;
                        int _y = y + j;

                        if (_x >= 0 && _x < input.rows && _y >= 0 && _y < input.cols) {
                            sum += input.at<Vec3b>(_x, _y)[c];
                            cnt++;
                        }
                    }
                }

                output.at<Vec3b>(x, y)[c] = static_cast<uchar>(sum / cnt);
            }
        }
    }
}
