#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void bilinear_interpolation(int x_size,int y_size,const Mat& img);

class TransformFunction
{
private:


    Mat M;
    Mat M_inv;

    vector<pair<int, int>> points_origin;
    vector<pair<int, int>> points_transformed;

    void solve_transform() // Calculate unknowns
    {
        Mat A(8, 6, CV_64F);
        Mat B(8, 1, CV_64F);

        //setting matrix
        for (int i = 0; i < 4; i++)
        {
            // x y 0 0 1 0
            A.at<double>(i * 2, 0) = points_origin[i].first;
            A.at<double>(i * 2, 1) = points_origin[i].second;
            A.at<double>(i * 2, 2) = 0;
            A.at<double>(i * 2, 3) = 0;
            A.at<double>(i * 2, 4) = 1;
            A.at<double>(i * 2, 5) = 0;

            B.at<double>(i * 2, 0) = points_transformed[i].first;

            // 0 0 x y 0 1
            A.at<double>(i * 2 + 1, 0) = 0;
            A.at<double>(i * 2 + 1, 1) = 0;
            A.at<double>(i * 2 + 1, 2) = points_origin[i].first;
            A.at<double>(i * 2 + 1, 3) = points_origin[i].second;
            A.at<double>(i * 2 + 1, 4) = 0;
            A.at<double>(i * 2 + 1, 5) = 1;

            B.at<double>(i * 2 + 1, 0) = points_transformed[i].second;
        }

        // Solve for unknowns (m1, m2, m3, m4)
        Mat X;
        solve(A,B,X,DECOMP_SVD);

        m1 = X.at<double>(0, 0);
        m2 = X.at<double>(1, 0);
        m3 = X.at<double>(2, 0);
        m4 = X.at<double>(3, 0);
        t1 = X.at<double>(4, 0);
        t2 = X.at<double>(5, 0);
    }

    void set_matrix()
    {
        M = (Mat_<double>(2, 2) << m1, m2, m3, m4);
    }

public:

    double m1;
    double m2;
    double m3;
    double m4;

    int t1;
    int t2;

    TransformFunction(vector<pair<int, int>> _points_origin, vector<pair<int, int>> _points_transformed)
    {
        this->points_origin = _points_origin;
        this->points_transformed = _points_transformed;
        solve_transform();
        set_matrix();
        invert(M,M_inv,DECOMP_SVD);
    }

    pair<int, int> returnTransformed(const int x, const int y)
    {
        Mat input = (Mat_<double>(2, 1) << x, y);
        Mat result = M_inv * (input + (Mat_<double>(2, 1) << -t1, -t2));

        int x_ = static_cast<int>(result.at<double>(0, 0));
        int y_ = static_cast<int>(result.at<double>(1, 0));

        return make_pair(x_, y_);
    }

};


int main()
{
    Mat input_img = imread("/home/junseo/2023-2/computer_vision/images/hw_6_img/lena_t.jpg");
    cvtColor(input_img, input_img, COLOR_BGR2GRAY);

    Mat transformed_img(input_img.rows,input_img.cols,input_img.type());    

    vector<pair<int,int>> origin = {{173, 284}, {477, 33}, {248, 455}, {553, 193}};
    vector<pair<int,int>> transformed = {{100, 100}, {412, 100}, {100, 412}, {412, 412}};
    TransformFunction func(origin, transformed);
    
    //debug
    cout<<func.m1<<endl;
    cout<<func.m2<<endl;
    cout<<func.m3<<endl;
    cout<<func.m4<<endl;
    cout<<func.t1<<endl;
    cout<<func.t2<<endl;


    pair<int,int> _pair;

    for (int x = 0; x < input_img.rows; x++) {
        for (int y = 0; y < input_img.cols; y++) {
            _pair = func.returnTransformed(x, y);
            if (_pair.first >= 0 && _pair.first < transformed_img.rows && _pair.second >= 0 && _pair.second < transformed_img.cols) {
                transformed_img.at<u_char>(_pair.first, _pair.second) = input_img.at<u_char>(x, y);
            }
        }
    }    
    imshow("original",input_img);
    imshow("transformed",transformed_img);
    waitKey(0);

    bilinear_interpolation(512,512, transformed_img);

    return 0;
}
void bilinear_interpolation(int x_size, int y_size, const Mat& img)
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