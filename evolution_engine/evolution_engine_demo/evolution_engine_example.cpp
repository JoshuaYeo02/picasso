#include "../evolution.h"
int main() {
    Evolution e1("../../img/totoro_target.png");
    int score = e1.score_frame();
    cout << score << endl;
    return 0;
}