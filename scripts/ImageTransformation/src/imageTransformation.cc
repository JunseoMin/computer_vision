#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class TransformFunction
{
private:
    Mat M;

public:
    TransformFunction(const vector<Point2f>& origin, const vector<Point2f>& transformed)
    {
        Mat A(2 * origin.size(), 6, CV_64F, Scalar(0));
        Mat B(2 * origin.size(), 1, CV_64F);

        for (int i = 0; i < origin.size(); ++i)
        {
            A.at<double>(2 * i, 0) = origin[i].x;
            A.at<double>(2 * i, 1) = origin[i].y;
            A.at<double>(2 * i, 2) = 1;

            A.at<double>(2 * i + 1, 3) = origin[i].x;
            A.at<double>(2 * i + 1, 4) = origin[i].y;
            A.at<double>(2 * i + 1, 5) = 1;

            B.at<double>(2 * i, 0) = transformed[i].x;
            B.at<double>(2 * i + 1, 0) = transformed[i].y;
        }

        Mat X;
        solve(A, B, X, DECOMP_SVD);

        M = Mat(3, 3, CV_64F);

        M.at<double>(0,0) = X.at<double>(0,0);     
        M.at<double>(0,1) = X.at<double>(1,0);     
        M.at<double>(0,2) = X.at<double>(2,0);     
        M.at<double>(1,0) = X.at<double>(3,0);     
        M.at<double>(1,1) = X.at<double>(4,0);     
        M.at<double>(1,2) = X.at<double>(5,0);
        M.at<double>(2,0) = 0;
        M.at<double>(2,1) = 0;
        M.at<double>(2,2) = 1;
        cout<<M;
    }

    Point2f transformPoint(const Point2f& point)
    {
        Mat pointMat = (Mat_<double>(3, 1) << point.x, point.y, 1);
        Mat transformedPoint = M * pointMat;

        return Point2f(static_cast<float>(transformedPoint.at<double>(0, 0)),
                       static_cast<float>(transformedPoint.at<double>(1, 0)));
    }
};

int main()
{
    Mat input_img = imread("/home/junseo/2023-2/computer_vision/images/hw_6_img/lena_t.jpg", IMREAD_GRAYSCALE);

    vector<Point2f> origin = {Point2f(173, 284), Point2f(477, 33), Point2f(248, 455), Point2f(553, 193)};
    vector<Point2f> transformed = {Point2f(100, 100), Point2f(412, 100), Point2f(100, 412), Point2f(412, 412)};
    TransformFunction transform(origin, transformed);

    Mat transformed_img(512, 512, input_img.type());

    for (int x = 0; x < input_img.rows; x++)
    {
        for (int y = 0; y < input_img.cols; y++)
        {
            Point2f transformed_point = transform.transformPoint(Point2f(y, x));

            int t_x = static_cast<int>(transformed_point.y);
            int t_y = static_cast<int>(transformed_point.x);

            if (t_x >= 0 && t_x < transformed_img.rows && t_y >= 0 && t_y < transformed_img.cols)
            {
                transformed_img.at<uchar>(t_x, t_y) = input_img.at<uchar>(x, y);
            }
        }
    }

    imshow("original", input_img);
    imshow("transformed", transformed_img);
    waitKey(0);

    return 0;
}
