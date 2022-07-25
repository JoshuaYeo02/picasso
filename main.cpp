#include "evolution_engine/evolution.h"
#include "img_engine/img.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void generateGif(string const filepath) {
    string command = "convert ./frames/frame*.png -loop 0 " + filepath + ".gif";
    system(command.c_str());
}

void generateVideo() {
    string command = "ffmpeg -y -r 60 -f image2 -s 860x1420 -i ./frames/frame%d.png -vcodec libx264 -crf 25 -pix_fmt yuv420p -vf pad=\"width=ceil(iw/2)*2:height=ceil(ih/2)*2\" ./frames/output.mp4";
    system(command.c_str());
}

int main() {
    string original_image_path = "img/totoro_target.png";
    string output_gif_path = "./frames/";
    string output_frames_path = "./frames/output";

    Evolution e = Evolution(original_image_path);
    e.natrual_selection(500, output_gif_path);
    generateVideo();
    //generateGif(output_frames_path);
}