#include "graphics.hpp"
#include<vector>
#include<cmath>
#include<cstdlib>

using namespace genv;
using namespace std;

const float WINDOW_WIDTH = 1024.;
const float WINDOW_HEIGHT = 768.;

void clear() {
    gout << move_to(0, 0);
    gout << color(25, 23, 36);
    gout << box_to(WINDOW_WIDTH,WINDOW_HEIGHT);
}

struct Vec2 {
public:
    float x;
    float y;

    Vec2(float x,float y) : x(x), y(y) {}
};


struct Ball {
private:
    Vec2 position;
    Vec2 velocity;
    float size;

public:
    Ball(Vec2 position,Vec2 velocity, float size) : position(position), velocity(velocity), size(size) {}

    void draw() {
        gout << move_to(this->position.x - (this->size/ 2.), this->position.y - (this->size / 2.));
        gout << color(49, 116, 143);
        gout << box(this->size, this->size);
    }
};


struct Model {
    vector<Ball> balls;

    Model() : balls(vector<Ball>()) {

        this->balls.push_back(
            Ball(
                Vec2(WINDOW_WIDTH/2.,WINDOW_HEIGHT/2.),
                Vec2(0.,0.),
                50.
            )
        );
    }
};

struct App {
private:
    Model model;

public:
    App() : model(Model()) {

        gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << refresh;
    }

    void event(const event &ev) {


    }
    void draw() {
        clear();

        for (Ball ball : this->model.balls) {
            ball.draw();
        }

        gout << refresh;
    }

};



int main()
{
    App app = App();

    event ev;
    while(gin >> ev)
    {
        app.event(ev);
        app.draw();
    }
    return 0;
}
