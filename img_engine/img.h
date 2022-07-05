#ifndef IMG_H
#define IMG_H

#include <png.h>
#include "pixel.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Img {
    private:
        int width;
        int height;
        vector<vector<Pixel>> pixels;
    public:
        Img();
        Img(int w, int h);
        Img(string const file);
        Img(Img const& o);
        ~Img();

        Pixel operator()(int x, int y);

        bool readFromFile(string const file);
        bool writeToFile (string const file);
        
        int getWidth();
        int getHeight();

        bool drawCircle(int x, int y, int r, int red, int green, int blue);
};



#endif