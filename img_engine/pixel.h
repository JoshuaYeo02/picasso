#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
    public:
        Pixel();
        Pixel(unsigned char red, unsigned char green, unsigned char blue);
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        int diff(Pixel p2);
};

#endif