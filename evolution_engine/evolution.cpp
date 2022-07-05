#include "evolution.h"

Evolution::Evolution(string const path) {
    target = Img(path);
    current_frame = Img(target.getWidth(), target.getHeight());
}