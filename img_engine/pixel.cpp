#include "pixel.h"
#include <cmath>

// Default constructor
Pixel::Pixel() {
    r = 0;
    g = 0;
    b = 0;
}

// Constructor
Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue) {
    r = red;
    g = green;
    b = blue;
    a = 255;
}

int Pixel::diff(Pixel p2) {
    return sqrt(
        pow((r - p2.r), 2) + 
        pow((g - p2.g), 2) + 
        pow((b - p2.b), 2)
        );
}

int Pixel::diff(int r2, int g2, int b2) {
    return sqrt(
        pow((r - r2), 2) + 
        pow((g - g2), 2) + 
        pow((b - b2), 2)
        );
}