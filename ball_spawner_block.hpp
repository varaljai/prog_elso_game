#ifndef BALL_SPAWNER_BLOCK_HPP_GUARD
#define BALL_SPAWNER_BLOCK_HPP_GUARD
#include "block.hpp"
#include "consts.hpp"
#include "vec2.hpp"
#include "graphics.hpp"
#include "block_action.hpp"

using namespace genv;

struct BallSpawnerBlock : public Block {
public:
    BallSpawnerBlock(Vec2 posison) : Block(posison, Vec2(BLOCK_WIDTH,BLOCK_HEIGHT)){}

    virtual void draw() override {
        gout << move_to(this->position.x - (this->size.x / 2.), this->position.y - (this->size.y / 2.));
        gout << color(235, 111, 146);
        gout << box(this->size.x, this->size.y);
    }

    virtual BlockAction hit() override {
        is_marked_for_remove = true;
        return SpawnBall;
    }

};

#endif // BALL_SPAWNER_BLOCK_HPP_GUARD