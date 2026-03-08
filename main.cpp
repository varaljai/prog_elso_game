#include "graphics.hpp"
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include "vec2.hpp"
#include "ball.hpp"
#include "consts.hpp"
#include "model.hpp"

using namespace genv;
using namespace std;

void clear() {
    gout << move_to(0, 0);
    gout << color(25, 23, 36);
    gout << box_to(WINDOW_WIDTH-1.,WINDOW_HEIGHT-1.);
}



struct App {
private:
    Model model;

public:
    App() : model(Model()) {
        srand(time(0));
        gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << refresh;
        gin.timer(FRAME_TIME);

    }

    void event(const event &ev) {
        if (ev.type == ev_timer) {
            for (int i=0; this->model.balls.size() > i; i++) {
                Ball &a_ball = this->model.balls[i];
                a_ball.update((float)FRAME_TIME /1000.); // TODO: el lehet-e kérni az eltelt időt?

                for (int j = i+1; this->model.balls.size() > j; j++) {
                    Ball &b_ball = this->model.balls[j];
                    a_ball.check_collision_with_a_ball_and_resolve(b_ball);

                }
            }


        }
    }

    void draw() {
        clear();

        for (Ball ball : this->model.balls) {
            ball.draw();
        }

        gout << refresh;
    }

};

int main() {
    App app = App();
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        app.event(ev);
        if (ev.type == ev_timer) {
            app.draw();
        }
    }
    return 0;
}
