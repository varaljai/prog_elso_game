#ifndef BALL_HPP_GUARD
#define BALL_HPP_GUARD

#include "graphics.hpp"
#include "consts.hpp"
#include "vec2.hpp"
#include "block.hpp"

#include <cmath>

using namespace genv;
using namespace std;

struct Ball {
private:
    Vec2 position;
    Vec2 velocity;
    float size;

    Vec2 closest(const Block &block) {
        return Vec2(
                max(min(this->position.x, (float)(block.get_position().x + block.get_size().x / 2.)), (float)(block.get_position().x - block.get_size().x / 2.)),
                max(min(this->position.y, (float)(block.get_position().y + block.get_size().y / 2.)), (float)(block.get_position().y - block.get_size().y / 2.))
        );
    }


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
    bool check_collision_with_a_block(const Block &block){
        float distance_squared = (this->position - this->closest(block)).lenght_squared();
        return distance_squared <= pow(this->size / 2.,2);
    }
};

#endif // BALL_HPP_GUARD