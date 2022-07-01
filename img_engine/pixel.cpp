#include "pixel.h"

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