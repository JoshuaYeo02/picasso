#include "evolution_engine/evolution.h"
#include "img_engine/img.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void generateGif(string const filepath) {
    string command = "convert ./img/frames/frame*.png -loop 0 " + filepath + ".gif";
    system(command.c_str());
}

int main() {
    string original_image_path = "img/totoro_target.png";
    string output_gif_path = "./output";
    string output_frames_path = "./img/frames/";

    Evolution e = Evolution(original_image_path);
    e.natrual_selection(500, output_frames_path);
    generateGif(output_frames_path);
}