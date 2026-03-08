#ifndef PADDLE_HPP_GUARD
#define PADDLE_HPP_GUARD
#include "block.hpp"
#include "consts.hpp"
#include "vec2.hpp"
#include "graphics.hpp"

using namespace genv;

struct Paddle : public Block {
public:
    float speed;
    bool move_to_left;
    bool move_to_right;

    Paddle() : Block(Vec2(WINDOW_WIDTH /2.,WINDOW_HEIGHT - PADDLE_HEIGHT),Vec2(PADDLE_WIDTH,PADDLE_HEIGHT)),
        move_to_left(false),
        move_to_right(false),
        speed(DEFAULT_PADDLE_SPEED) {}

    virtual void draw() {
        gout << move_to(this->position.x - (this->size.x / 2.), this->position.y - (this->size.y / 2.));
        gout << color(49, 116, 143);
        gout << box(this->size.x, this->size.y);
    }

    void update(float dt) {
        if (move_to_left) {
            this->position.x -= this->speed * dt;
        }
        if (move_to_right) {
            this->position.x += this->speed * dt;
        }

        if (this->position.x + this->size.x / 2. > WINDOW_WIDTH -1.) {
            this->position.x = WINDOW_WIDTH -1. - this->size.x / 2.;
        }
        else if (this->position.x - this->size.x / 2. < 0.) {
            this->position.x = 0. + this->size.x / 2.;
        }
    }
};

#endif // PADDLE_HPP_GUARD