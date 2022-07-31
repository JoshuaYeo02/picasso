#include "evolution.h"
#include <cmath>
using namespace std;

Evolution::Evolution(string const path) {
    target = Img(path);
    int width = target.getWidth();
    int height = target.getHeight();
    current_frame = Img(width, height);
    pixel_difference.resize(height, vector<int>(width, 0));
    current_score = score_frame();
    srand(time(0));
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
            int distance = p1.diff(p2);
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

/*int Evolution::score_frame(int x, int y, int radius, int r, int g, int b) {
    Img current_frame_copy(current_frame);
    current_frame_copy.drawCircle(x, y, radius, r, g, b);
    int height = target.getHeight();
    int width = target.getWidth();
    int diff_score = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Pixel p1 = target(x, y);
            Pixel p2 = current_frame_copy(x, y);
            // Geometric algorithm - equal weighting of all colours
            int difference = p1.diff(p2);
            diff_score += difference;
        }
    }
    return diff_score;
}*/

int Evolution::score_frame(int x, int y, int radius, int r, int g, int b) {
    int new_score = current_score;
    vector<pair<int, int>> pixel_coordinates = target.circleRange(x, y, radius);
    for (pair<int, int> coordinate : pixel_coordinates) {
        int px = coordinate.first;
        int py = coordinate.second;
        new_score += (target(px, py).diff(r, g, b) - pixel_difference[py][px]);
    }
    return new_score;
}

pair<int, vector<int>> Evolution::generation() {
    vector<pair<int, vector<int>>> children_data;
    pair<int, vector<int>> min_data;
    int min = 999999999;
    for (int i = 0; i < 100; i++) {
        vector<int> circle_data = generate_circle();
        int score = score_frame(circle_data[0], circle_data[1], circle_data[2], circle_data[3], circle_data[4], circle_data[5]);
        children_data.push_back(make_pair(score, circle_data));
        if (score < min) {
            min = score;
            min_data = children_data[i];
        }
    } 
    // pair<int, vector<int>> min = children_data[0];
    // for (pair<int, vector<int>> p : children_data) {
    //     if (p.first < max.first) {
    //         min = p;
    //     }
    // }
    return min_data;
}

void Evolution::natrual_selection(int iterations, string const path) {
    vector<pair<int, vector<int>>> children_data;
    for (int i = 0; i < iterations; i++) {
        pair<int, vector<int>> new_child = generation();
        vector<pair<int, int>> pixel_coordinates = target.circleRange(new_child.second[0], 
                                                            new_child.second[1], new_child.second[2]);
        for (pair<int, int> p : pixel_coordinates) {
            pixel_difference[p.second][p.first] = target(p.first, p.second).diff(new_child.second[3], 
                                                                    new_child.second[4], new_child.second[5]);
        }
        current_frame.drawCircle(new_child.second[0], new_child.second[1], 
                                 new_child.second[2], new_child.second[3], 
                                 new_child.second[4], new_child.second[5]);
        current_score = new_child.first;
        current_frame.writeToFile(path + "frame" + to_string(i) + ".png");
    }
}