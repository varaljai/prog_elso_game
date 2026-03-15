#ifndef MODEL_HPP_GUARD
#define MODEL_HPP_GUARD

#include <vector>

#include "ball.hpp"
#include "ball_spawner_block.hpp"
#include "vec2.hpp"
#include "consts.hpp"
#include "normal_block.hpp"
#include "paddle.hpp"
#include "strong_block.hpp"


using namespace std;

struct Model {
    vector<Ball> balls;
    Paddle paddle;
    vector<Block*> blocks;

    Model() : balls(vector<Ball>()), paddle(Paddle()), blocks(vector<Block*>()) {
        this->balls.push_back(Ball(this->paddle.get_position()));
        Vec2 m = Vec2(WINDOW_WIDTH / (BLOCK_WIDTH + PAD_BETWEEN_BLOCKS),WINDOW_HEIGHT /(BLOCK_HEIGHT + PAD_BETWEEN_BLOCKS));
        for (int y = 2; m.y / 2. > y; y++) {
            for (int x = 1; m.x -1 > x; x++ ) {
                Vec2 pos = Vec2((float)x * (BLOCK_WIDTH + PAD_BETWEEN_BLOCKS),(float)y * (BLOCK_HEIGHT + PAD_BETWEEN_BLOCKS));
                switch (rand()%3) {
                    case 0:
                        this->blocks.push_back(new NormalBlock(pos));
                        break;
                    case 1:
                        this->blocks.push_back(new BallSpawnerBlock(pos));
                        break;
                    case 2:
                        this->blocks.push_back(new StrongBlock(pos));
                        break;
                    default:
                        break;
                }
            }
        }

    }
    ~Model() {
        while (this->blocks.size() > 0 ) {
            delete this->blocks[this->blocks.size()-1];
            this->blocks.pop_back();
        }
    }
};

#endif // MODEL_HPP_GUARD

