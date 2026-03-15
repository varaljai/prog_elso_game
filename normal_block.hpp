#ifndef NORMAL_BLOCK_HPP_GUARD
#define NORMAL_BLOCK_HPP_GUARD
#include "block.hpp"
#include "consts.hpp"
#include "vec2.hpp"
#include "graphics.hpp"

using namespace genv;

struct NormalBlock : public Block {
public:
    NormalBlock(Vec2 posison) : Block(posison, Vec2(BLOCK_WIDTH,BLOCK_HEIGHT)){}

    virtual void draw() override {
        gout << move_to(this->position.x - (this->size.x / 2.), this->position.y - (this->size.y / 2.));
        gout << color(49, 116, 143);
        gout << box(this->size.x, this->size.y);
    }

    virtual void hit() override {
        is_marked_for_remove = true;
    }

};

#endif // NORMAL_BLOCK_HPP_GUARD