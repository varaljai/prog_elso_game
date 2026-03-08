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

};



#endif // BLOCK_HPP_GUARD