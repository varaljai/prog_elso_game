#ifndef MODEL_HPP_GUARD
#define MODEL_HPP_GUARD

#include <vector>

#include "ball.hpp"
#include "vec2.hpp"
#include "consts.hpp"
#include "normal_block.hpp"
#include "paddle.hpp"



using namespace std;

struct Model {
    vector<Ball> balls;
    Paddle paddle;
    vector<Block*> blocks;

    Model() : balls(vector<Ball>()), paddle(Paddle()), blocks(vector<Block*>()) {
        this->balls.push_back(
             Ball(
                 this->paddle.get_position(),
                 Vec2((float)(rand()%240-120),(float)(rand()%240-120)),
                 (float)(rand()%15+5)
             )
        );
        this->blocks.push_back(new NormalBlock(Vec2(WINDOW_WIDTH / 2., WINDOW_HEIGHT / 2.)));

    }
    ~Model() {
        while (this->blocks.size() > 0 ) {
            delete this->blocks[this->blocks.size()-1];
            this->blocks.pop_back();
        }
    }
};

#endif // MODEL_HPP_GUARD

