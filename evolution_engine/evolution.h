#ifndef EVOLTUION_H
#define EVOLTUION_H
#include "../img_engine/img.h"
#include <vector>
#include <string>

class Evolution {
    public:
        Img target;
        Img current_frame;
        vector<vector<int>> pixel_difference;
        // generates new circle, Return type should not be void
        void new_frame();
        // Returns the difference score between current and target img
        int score_frame();
        // returns the score between current + a cirlce and target img
        int score_frame(int x, int y, int radius, int r, int g, int b);
    public:
        Evolution(string const path);
        void natrual_selection(int iterations, string const path);

};

#endif