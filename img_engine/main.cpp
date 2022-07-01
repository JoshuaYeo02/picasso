#include "img.h"
#include <iostream>
using namespace std;
int main() {
    Img tmp(400, 400);
    cout << tmp.getWidth() << " " << tmp.getHeight() << endl;
    cout << (int) tmp(0,0).r << " " << (int) tmp(0, 0).g << " " << (int) tmp(0, 0).b << endl;
    tmp.writeToFile("../img/output.png");
}