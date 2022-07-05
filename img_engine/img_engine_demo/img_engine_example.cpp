#include "../img.h"
#include <iostream>
using namespace std;
int compare(Img originla, Img curent) {
    // cxompare images


    return score;
}
int main() {
    // To create a new Img that is a copy of a PNG
    Img t2("img/totoro_target.png");
    // To crate a blank img that smae diemosns as t2 
    Img t3(t2.getWidth(), t2.getHeight()); 
    cout << compare(t2, t3) << endl;
}