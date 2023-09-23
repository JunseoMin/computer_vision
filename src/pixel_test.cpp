#include <iostream>

using namespace std;

int main(void){
    unsigned char pix1,pix2;
    pix1=255;
    pix2=1;
    cout<<pix1+pix2<<endl;
    pix1=0;
    pix2=1;
    cout<<pix1-pix2;
    //왜됨??
    return 0;
}