#ifndef BLOCK_HPP_GUARD
#define BLOCK_HPP_GUARD
#include "vec2.hpp"

struct Block {
protected:
    Vec2 position;
    Vec2 size;
    bool is_marked_for_remove;
public:
    Block(Vec2 block_position, Vec2 block_size) : position(block_position), size(block_size), is_marked_for_remove(false) {}
    virtual void draw() {}
    virtual void hit() {}

    Vec2 get_position() const {
        return this->position;
    }

    Vec2 get_size() const {
        return this->size;
    }

    bool get_is_marked_for_remove() const {
        return this->is_marked_for_remove;
    }


};



#endif // BLOCK_HPP_GUARD