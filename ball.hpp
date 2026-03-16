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
    bool is_marked_for_remove;

    Vec2 closest(const Block* block) const {
        const Vec2 pos = block->get_position();
        const Vec2 half = block->get_size() * 0.5;
        return Vec2(
            max(pos.x - half.x, min(this->position.x, pos.x + half.x)),
            max(pos.y - half.y, min(this->position.y, pos.y + half.y))
        );
    }


public:
    Ball(Vec2 ball_position,Vec2 ball_velocity, float ball_size) : position(ball_position), velocity(ball_velocity), size(ball_size), is_marked_for_remove(false){}
    Ball(Vec2 ball_position) : position(ball_position),
        velocity(Vec2(0.1, -1.) * ((float)( rand()%(int)(BALL_MAX_VELOCITY - BALL_MIN_VELOCITY) ) + BALL_MIN_VELOCITY)),
        size((float)( rand()%(int)(BALL_MAX_SIZE - BALL_MIN_SIZE) ) + BALL_MIN_SIZE),
        is_marked_for_remove(false) {
        this->position.y -= this->size;
    }

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
            this->is_marked_for_remove = true;
            this->position.y = WINDOW_HEIGHT -1. - this->size / 2.;
        }
        else if (this->position.y - this->size / 2. < 0.) {
            this->velocity.y *= -1.;
            this->position.y = 0. + this->size / 2.;
        }

    }
    void check_collision_with_a_ball_and_resolve(Ball &other){
        if (pow(this->size / 2. + other.size / 2.,2) > (this->position - other.position).length_squared() ) {
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
    bool check_collision_with_block(Block* block, Vec2& out_normal, Vec2& out_closest) {
        out_closest = this->closest(block);
        Vec2 diff = this->position - out_closest;
        float dist_sq = diff.length_squared();
        float radius = this->size * 0.5;

        if (dist_sq > radius * radius)
            return false;

        if (dist_sq > 0.) {
            out_normal = diff * (1. / sqrt(dist_sq));
        } else {
            float vel_sq = this->velocity.length_squared();
            if (vel_sq > 0.) {
                out_normal = this->velocity * (1. / sqrt(vel_sq));
            }
            else {
                Vec2(0., 1.);
            }

        }
        return true;
    }

    void paddled(Vec2 paddle_pos) {
        Vec2 direction = (this->position - paddle_pos).normalize();
        this->velocity = direction * this->velocity.length();
    }

    void block_hit(Vec2& normal) {
        float dot = this->velocity.dot(normal);
        this->velocity = this->velocity - normal * (dot * 2.);
    }

    bool get_is_marked_for_remove() const {
        return this->is_marked_for_remove;
    }
};

#endif // BALL_HPP_GUARD