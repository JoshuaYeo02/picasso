#include "evolution.h"
#include <cmath>
using namespace std;

Evolution::Evolution(string const path) {
    target = Img(path);
    current_frame = Img(target.getWidth(), target.getHeight());
    pixel_difference.resize(target.getHeight(), vector<int>(target.getWidth(), 0));
}

int Evolution::score_frame() {
    int height = target.getHeight();
    int width = target.getWidth();
    int diff_score = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel p1 = target(x, y);
            Pixel p2 = current_frame(x, y);
            // Geometric algorithm - equal weighting of all colours
            int distance = sqrt(
                pow((p1.r - p2.r), 2) + 
                pow((p1.g - p2.g), 2) + 
                pow((p1.b - p2.b), 2)
                );
            /*
            // A 'redmean' formula on Wikipedia that's supposed to
            // to match human perception better
            int distance = sqrt(
                (2 + (p1.r + p2.r) / 512) * pow((p1.r - p2.r), 2) + 
                4 * pow((p1.g - p2.g), 2) + 
                (3 - (p1.r + p2.r) / 512) * pow((p1.b - p2.b), 2)
                );
            */
            pixel_difference[y][x] = distance;
            diff_score += distance;
        }
    }
    return diff_score;
}

vector<int> Evolution::generate_circle() {
    vector<int> circle_data;
    // x and y coords of circle center
    circle_data.push_back(rand() % target.getWidth());
    circle_data.push_back(rand() % target.getHeight());
    // radius of circle
    circle_data.push_back(rand() % (max(target.getHeight(), target.getWidth()) / 2));
    // r g b values
    circle_data.push_back(rand() % 256);
    circle_data.push_back(rand() % 256);
    circle_data.push_back(rand() % 256);

    return circle_data;
}