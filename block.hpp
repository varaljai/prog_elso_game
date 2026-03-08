#ifndef BLOCK_HPP_GUARD
#define BLOCK_HPP_GUARD
#include "vec2.hpp"

struct Block {
protected:
    Vec2 position;
    Vec2 size;
public:
    Block(Vec2 position, Vec2 size) : position(position), size(size)  {}
    virtual void draw() {}

    Vec2 get_position() const {
        return this->position;
    }

    Vec2 get_size() const {
        return this->size;
    }

};



#endif // BLOCK_HPP_GUARD