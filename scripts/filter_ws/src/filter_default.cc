#define kernal_size 9
#define FILTER_SIZE 9

#include <iostream>
#include <opencv2/opencv.hpp>

void padding(void);
void zero_padding(int select);
void repetition_padding(void);
void mirror_padding(void);

void filtering(int filter_size, Mat img_input);

using namespace std;
using namespace cv;

int main(void){
    Mat color_img;
    Mat gray_img;
    Mat padded;

    double kernal[kernal_size]; 

    color_img=imread("/home/junseo/2023-2/computer_vision/images/kkang_tae.jpg");
    
    cvtColor(color_img,gray_img,COLOR_BGR2GRAY);

    filtering(FILTER_SIZE, color_img);
    filtering(FILTER_SIZE,gray_img);

    return 0;
}

void padding(int select)
// select: 1 = zero_padding , 2 = repetition_padding , 3 = mirror_padding
{
    switch (select)
    {
    case 1:
        zero_padding();
        break;
    
    case 2:
        repetition_padding();
        break;

    case 3:
        mirror_padding();
        break;

    default:
        cout<<"not selected"<<endl;
        break;
    }
}

void zero_padding(){

}

void repetition_padding(){

}

void mirror_padding(){

}

void filtering(int filter_size, Mat img_input)
{

}