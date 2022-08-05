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

pair<int, vector<int>> Evolution::mutate(vector<int> circle_data) {
    int mutation_type = rand() % 3;
    // these are arbitraily chosen
    // mutate color
    if (mutation_type == 0) {
        // choose which rgb stream to change
        int color_stream = rand() % 3;
        // choose amount to change thats non 0 between -5, 5
        int change_amount = rand() % 11 - 5;
        while (change_amount == 0) {
            change_amount = rand() % 11 - 5;
        }
        // change color stream
        if (color_stream == 0) {
            if (circle_data[3] + change_amount < 0) {
                circle_data[3] = 0;
            } else if (circle_data[3] + change_amount > 255) {
                circle_data[3] = 255;
            } else {
                circle_data[3] += change_amount;
            }
        } else if (color_stream == 1) {
            if (circle_data[4] + change_amount < 0) {
                circle_data[4] = 0;
            } else if (circle_data[4] + change_amount > 255) {
                circle_data[4] = 255;
            } else {
                circle_data[4] += change_amount;
            }
        } else {
            if (circle_data[5] + change_amount < 0) {
                circle_data[5] = 0;
            } else if (circle_data[5] + change_amount > 255) {
                circle_data[5] = 255;
            } else {
                circle_data[5] += change_amount;
            }
        }
    } else if (mutation_type == 1) { // mutate size
        // choose how much to change size by
        int change_amount = rand() % 7 - 3;
        while (change_amount == 0) {
            change_amount = rand() % 7 - 3;
        }
        circle_data[2] += change_amount;
    } else { // mutate location
        // choose whihc coord to change
        int coord = rand() % 2;
        // choose how much to change by
        int change_amount = rand() % 7 - 3;
        while (change_amount == 0) {
            change_amount = rand() % 7 - 3;
        }
        if (coord == 0) {
            if (circle_data[0] + change_amount < 0) {
                circle_data[0] = 0;
            } else if (circle_data[0] + change_amount >= target.getWidth()) {
                circle_data[0] = target.getWidth() - 1;
            } else {
                circle_data[0] += change_amount;
            }
        } else {
            if (circle_data[1] + change_amount < 0) {
                circle_data[1] = 0;
            } else if (circle_data[1] + change_amount >= target.getHeight()) {
                circle_data[1] = target.getHeight() - 1;
            } else {
                circle_data[1] += change_amount;
            }
        }
    }
    int score = score_frame(circle_data[0], circle_data[1], circle_data[2], circle_data[3], circle_data[4], circle_data[5]);
    return make_pair(score, circle_data);
}

pair<int, vector<int>> Evolution::mutation(vector<int> circle_data, int mutations) {
    pair<int, vector<int>> min_child;
    int min_score = 2147483647;
    for (int i = 0; i < mutations; i++) {
        pair<int, vector<int>> mutated_child = mutate(circle_data);
        if (mutated_child.first < min_score) {
            min_child = mutated_child;
        }
    }
    return min_child;
}

pair<int, vector<int>> Evolution::generation(int generations, int cutoff, int mutations) {
    vector<pair<int, vector<int>>> children_data;

    // Get generations of children
    for (int i = 0; i < generations; i++) {
        vector<int> circle_data = generate_circle();
        int score = score_frame(circle_data[0], circle_data[1], circle_data[2], circle_data[3], circle_data[4], circle_data[5]);
        children_data.push_back(make_pair(score, circle_data));
    } 

    // soort children and take the top cutoff number of children
    sort(children_data.begin(), children_data.end(), [](auto &l, auto &r) { return l.first < r.first;});
    children_data.erase(children_data.begin() + cutoff, children_data.end());

    // mutate the top children and take the best
    pair<int, vector<int>> min_data = children_data[0];
    for (pair<int, vector<int>> p : children_data) {
       pair<int, vector<int>> mutated_child = mutation(p.second, mutations);
       if (mutated_child.first < min_data.first) {
            min_data = mutated_child;
       }
    }
    return min_data;
}

void Evolution::natrual_selection(int iterations, int generations, int cutoff, int mutations, string const path) {
    vector<pair<int, vector<int>>> children_data;
    for (int i = 1; i <= iterations; i++) {
        pair<int, vector<int>> new_child = generation(generations, cutoff, mutations);
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
        cout << "Frame " << i << endl;
        cout << "Current Score: " << current_score << endl;
    }
}