#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;




vector<int> solve_trasnform(vector<vector<int>> points_origin, vector<vector<int>> points_transformed); // calc unknowns
vector<int> trasnform_math(const int m1, const int m2 ,const int m3 , const int m4,const int t1, const int t2, const int input_x, const int input_y); // inner function: transformation(x,y array calc)
void transform(const Mat& input, Mat& output);
void interpolation(const Mat& input, Mat& output);


int main()
{
    Mat input_img = imread("/home/junseo/2023-2/computer_vision/images/hw_6_img/lena_t.jpg");    
    Mat transformed_img;    



    imshow("original",input_img);
    waitKey(0);


    return 0;
}

void transform(const Mat& input, Mat& output){
    vector<int> vec;

    for (int x = 0; x < input.cols; x++)
        {
            for (int y = 0; y < input.rows; y++)
            {
                input.at<uchar>(x, y);
                trasnform_math(v);

            }
        }
    
}
