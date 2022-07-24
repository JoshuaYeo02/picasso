#include "../evolution.h"
int main() {
    Evolution e1("../../img/totoro_target.png");
    int score = e1.score_frame();
    int score2 = e1.score_frame(100, 100, 50, 255, 255, 255);
    cout << score << endl;
    cout << score2 << endl;
    return 0;
}