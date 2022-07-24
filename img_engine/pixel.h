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
        
        // Finds colour difference between this pixel and another
        int diff(Pixel p2);
        int diff(int r2, int g2, int b2);
};

#endif