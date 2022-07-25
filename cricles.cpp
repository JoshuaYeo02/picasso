#include "evolution_engine/evolution.h"
#include "img_engine/img.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void generateGif(string const filepath) {
    string command = "convert ./frames/circles*.png -loop 0 " + filepath + ".gif";
    system(command.c_str());
}

int main() {
    string original_image_path = "img/totoro_target.png";
    string output_gif_path = "./frames";
    string output_frames_path = "./frames/output";

    Evolution e = Evolution(original_image_path);
    for (int i = 0; i < 100; i++) {
        vector<int> circle_data = e.generate_circle();
        e.current_frame.drawCircle(circle_data[0], circle_data[1], circle_data[2], circle_data[3], circle_data[4], circle_data[5]);
        e.current_frame.writeToFile("./frames/circles" + to_string(i) + ".png");
    }
    //e.natrual_selection(500, output_frames_path);
    generateGif(output_frames_path);
}