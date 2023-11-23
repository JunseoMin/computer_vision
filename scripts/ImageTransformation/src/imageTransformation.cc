#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;
class TransformFunction
{
private:
    double m1;
    double m2;
    double m3;
    double m4;
    Mat M;

    vector<pair<int, int>> points_origin;
    vector<pair<int, int>> points_transformed;

    void solve_transform() // Calculate unknowns
    {
        Mat A(points_origin.size() * 2, 4, CV_64F);
        Mat B(points_origin.size() * 2, 1, CV_64F);

        for (int i = 0; i < points_origin.size(); ++i)
        {
            A.at<double>(i * 2, 0) = points_origin[i].first;
            A.at<double>(i * 2, 1) = points_origin[i].second;
            A.at<double>(i * 2, 2) = 1;
            A.at<double>(i * 2, 3) = 0;

            B.at<double>(i * 2, 0) = points_transformed[i].first;

            A.at<double>(i * 2 + 1, 0) = 0;
            A.at<double>(i * 2 + 1, 1) = 0;
            A.at<double>(i * 2 + 1, 2) = points_origin[i].first;
            A.at<double>(i * 2 + 1, 3) = points_origin[i].second;

            B.at<double>(i * 2 + 1, 0) = points_transformed[i].second;
        }

        // Solve for unknowns (m1, m2, t1, t2)
        Mat X;
        solve(A, B, X, DECOMP_SVD);

        m1 = X.at<double>(0, 0);
        m2 = X.at<double>(1, 0);
        m3 = X.at<double>(2, 0);
        m4 = X.at<double>(3, 0);
    }

    void set_matrix()
    {
        M = (Mat_<double>(2, 2) << m1, m2, m3, m4);
    }

public:
    TransformFunction(vector<pair<int, int>> _points_origin, vector<pair<int, int>> _points_transformed)
    {
        this->points_origin = _points_origin;
        this->points_transformed = _points_transformed;
        solve_transform();
        set_matrix();
    }

    pair<int, int> returnTransformed(const int x, const int y)
    {
        Mat input = (Mat_<double>(2, 1) << x, y);
        Mat result = M * input;

        int x_ = static_cast<int>(result.at<double>(0, 0));
        int y_ = static_cast<int>(result.at<double>(1, 0));

        return make_pair(x_, y_);
    }
};

int main()
{
    Mat input_img = imread("/home/junseo/2023-2/computer_vision/images/hw_6_img/lena_t.jpg");    
    Mat transformed_img;    

    vector<pair<int,int>> origin = {{173, 284}, {477, 33}, {248, 455}, {553, 193}};
    vector<pair<int,int>> transformed = {{100, 100}, {412, 100}, {100, 412}, {412, 412}};

    TransformFunction(origin, transformed);


    imshow("original",input_img);
    waitKey(0);


    return 0;
}
