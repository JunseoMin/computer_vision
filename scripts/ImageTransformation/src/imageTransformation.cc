#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void bilinear_interpolation(int x_size,int y_size,const Mat& img);

class TransformFunction
{
private:
    Mat A;
    Mat B;

    Mat A_inv;

    double m1;
    double m2;
    double m3;
    double m4;

    int t1;
    int t2;

    Mat M;
    Mat M_inv;

    vector<pair<int, int>> points_origin;
    vector<pair<int, int>> points_transformed;

    void solve_transform() // Calculate unknowns
    {
        // Solve for unknowns (m1, m2, m3, m4)
        Mat X;
        solve(A,B,X,DECOMP_SVD);

        m1 = X.at<double>(0, 0);
        m2 = X.at<double>(1, 0);
        m3 = X.at<double>(2, 0);
        m4 = X.at<double>(3, 0);
        t1 = X.at<double>(4, 0);
        t2 = X.at<double>(5, 0);
        cout<<X<<endl;
    }

    void set_matrix()
    {
        M = (Mat_<double>(2, 2) << m1, m2, m3, m4);
        M_inv = invert(M,M_inv,DECOMP_SVD);
        cout<<M<<endl;
    }

    void set_clac_matrix()
    {
        //setting A,B size
        A = A.zeros(2*points_origin.size(),6,CV_64F);
        B = B.zeros(2*points_origin.size(),1,CV_64F);
        //setting matrix
        for (int i = 0; i < points_origin.size(); i++)
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

        //debug
        // cout<<A<<endl;
        // cout<<B<<endl;
        //
        // invert(A,A_inv,DECOMP_SVD);
        // cout<<A_inv<<endl;
        // cout<<A*A_inv<<endl;
    }

public:

    TransformFunction(vector<pair<int, int>> _points_origin, vector<pair<int, int>> _points_transformed)
    {
        this->points_origin = _points_origin;
        this->points_transformed = _points_transformed;
        set_clac_matrix();
        solve_transform();
        set_matrix();
    }

    pair<int, int> returnTransformed(const int x, const int y)
    {
        Mat input = (Mat_<double>(2, 1) << x, y);
        Mat result = M * input + (Mat_<double>(2, 1) << t1, t2);

        int x_ = static_cast<int>(result.at<double>(0, 0));
        int y_ = static_cast<int>(result.at<double>(1, 0));

        return make_pair(x_, y_);
    }

};


int main()
{
    Mat input_img = imread("/home/junseo/2023-2/computer_vision/images/hw_6_img/lena_t.jpg");
    cvtColor(input_img, input_img, COLOR_BGR2GRAY);

    Mat transformed_img(512,512,input_img.type());    
    float _x = (input_img.rows/512.0);
    float _y = (input_img.cols/512.0);
    vector<pair<int,int>> origin = {{173, 284}, {477, 33}, {248, 455}, {553, 193}};
    vector<pair<int,int>> transformed = {{100, 100}, {412, 100}, {100, 412}, {412, 412}};
    TransformFunction func(origin, transformed);
    
    // //debug
    // cout<<func.m1<<endl;
    // cout<<func.m2<<endl;
    // cout<<func.m3<<endl;
    // cout<<func.m4<<endl;
    // cout<<func.t1<<endl;
    // cout<<func.t2<<endl;

    cout<<func.returnTransformed(173,284).first;
    cout<<func.returnTransformed(173,284).second<<endl;

    pair<int,int> _pair;

    int t_x;
    int t_y;

    for (int x = 0; x < input_img.rows; x++) {
        for (int y = 0; y < input_img.cols; y++) {
            _pair = func.returnTransformed(x, y);
            t_x = static_cast<int>(_pair.first * _x);
            t_y = static_cast<int>(_pair.second * _y);
            if (t_y>400)
            {
                cout<<t_y<<endl;
                /* code */
            }
            
            transformed_img.at<u_char>(t_x, t_y) = input_img.at<u_char>(x, y);
        }
    }    
    
    // imshow("original",input_img);
    // imshow("transformed",transformed_img);
    // waitKey(0);

    // bilinear_interpolation(512,512, transformed_img);

    return 0;
}