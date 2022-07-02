#include "../img.h"
#include <iostream>
using namespace std;
int main() {
    // To create a new Img of size 1920x1080, defualt color is 128, 128, 128
    Img t1(1920, 1080);
    // To create a new Img that is a copy of a PNG
    Img t2("img/totoro_target.png");
    // To copy another image
    Img t3(t2); 
    // To get a pixel from an img (x,y)
    t1(0,0);
    // To output an img 
    t1.writeToFile("img/output.png");
    // get to img dimensions
    t1.getHeight();
    t1.getWidth();
}