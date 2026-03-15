#ifndef STRONG_BLOCK_HPP_GUARD
#define STRONG_BLOCK_HPP_GUARD
#include "block.hpp"
#include "consts.hpp"
#include "vec2.hpp"
#include "graphics.hpp"

using namespace genv;

struct StrongBlock : public Block {
private:
    int hp;
public:
    StrongBlock(Vec2 posison) : Block(posison, Vec2(BLOCK_WIDTH,BLOCK_HEIGHT)), hp(3){}

    virtual void draw() override {
        gout << move_to(this->position.x - (this->size.x / 2.), this->position.y - (this->size.y / 2.));
        gout << color(246, 193, 119);
        gout << box(this->size.x, this->size.y);
        gout << move_to(this->position.x - (this->size.x / 2.), this->position.y - (this->size.y / 2.));
        gout << color(25, 23, 36);
        gout << text(string(this->hp,'O'));
    }

    virtual BlockAction hit() override {
        this->hp--;
        if (this->hp <= 0) {
            is_marked_for_remove = true;
        }
        return DoNothing;
    }

};

#endif // STRONG_BLOCK_HPP_GUARD