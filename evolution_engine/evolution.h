#ifndef EVOLTUION_H
#define EVOLTUION_H
#include "../img_engine/img.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm> 
class Evolution {
    public:
        Img target;
        Img current_frame;
        vector<vector<int>> pixel_difference;
        int current_score;
        // generates new circle, Return type should not be void
        void new_frame();
        // Returns the difference score between current and target img
        int score_frame();
        // returns the score between current + a cirlce and target img
        int score_frame(int x, int y, int radius, int r, int g, int b);
        // returns an vector of the info for a circle
        // of form {x, y, r, red, green, blue}
        vector<int> generate_circle();
    public:
        Evolution(string const path);
        void natrual_selection(int iterations, string const path);

};

#endif