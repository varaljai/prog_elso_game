#include "graphics.hpp"
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iostream>

using namespace genv;
using namespace std;

const float WINDOW_WIDTH = 1024.;
const float WINDOW_HEIGHT = 768.;
const int FRAME_TIME = 16;  // kb 60 fps

void clear() {
    gout << move_to(0, 0);
    gout << color(25, 23, 36);
    gout << box_to(WINDOW_WIDTH-1.,WINDOW_HEIGHT-1.);
}

struct Vec2 {
public:
    float x;
    float y;

    Vec2(float x,float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &other) {
        return Vec2(this->x + other.x, this->y + other.y);
    }

    Vec2 operator-(const Vec2 &other) {
        return Vec2(this->x - other.x, this->y - other.y);
    }

    Vec2 operator*(const float &other) {
        return Vec2(this->x * other, this->y * other);
    }

    Vec2 operator/(const float &other) {
        return Vec2(this->x / other, this->y / other);
    }

    float lenght_squared() {
        return this->x*this->x + this->y*this->y;
    }

    float lenght() {
        return sqrt(this->lenght_squared());
    }

    Vec2 normalize() {
        return *this / this->lenght();
    }

    float dot(const Vec2 &other) {
        return this->x * other.x + this->y * other.y;
    }
};


struct Ball {
private:
    Vec2 position;
    Vec2 velocity;
    float size;

public:
    Ball(Vec2 position,Vec2 velocity, float size) : position(position), velocity(velocity), size(size){}

    void draw() {
        gout << move_to(this->position.x - (this->size/ 2.), this->position.y - (this->size / 2.));
        gout << color(49, 116, 143);
        gout << box(this->size, this->size);
    }

    void update(float dt) {
        this->position = this->position + (this->velocity * dt);
        if (this->position.x + this->size / 2. > WINDOW_WIDTH -1.) {
            this->velocity.x *= -1.;
            this->position.x = WINDOW_WIDTH -1. - this->size / 2.;
        }
        else if (this->position.x - this->size / 2. < 0.) {
            this->velocity.x *= -1.;
            this->position.x = 0. + this->size / 2.;
        }

        if (this->position.y + this->size / 2. > WINDOW_HEIGHT -1.) {
            this->velocity.y *= -1.;
            this->position.y = WINDOW_HEIGHT -1. - this->size / 2.;
        }
        else if (this->position.y - this->size / 2. < 0.) {
            this->velocity.y *= -1.;
            this->position.y = 0. + this->size / 2.;
        }
    }
    void check_collision_with_a_ball_and_resolve(Ball &other){
        if (pow(this->size / 2. + other.size / 2.,2) > (this->position - other.position).lenght_squared() ) {
            Vec2 collision_normal = (this->position - other.position).normalize();
            Vec2 relative_velocity = (this->velocity - other.velocity);
            float velocity_along_normal = relative_velocity.dot(collision_normal) ;
            if (velocity_along_normal >= 0.) {
                return;
            }
            Vec2 impulse = collision_normal * velocity_along_normal;
            this->velocity = this->velocity - impulse;
            other.velocity = other.velocity + impulse;
        }

    }
};


struct Model {
    vector<Ball> balls;

    Model() : balls(vector<Ball>()) {
        for (int i = 0; 20 > i; i++ ) {
            this->balls.push_back(
             Ball(
                 Vec2((float)(rand()%(int)WINDOW_WIDTH),(float)(rand()%(int)WINDOW_HEIGHT)),
                 Vec2((float)(rand()%120-60),(float)(rand()%120-60)),
                 (float)(rand()%15+5)
             )
         );
        }
    }
};

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
