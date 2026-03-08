#ifndef MODEL_HPP_GUARD
#define MODEL_HPP_GUARD

#include <vector>

#include "ball.hpp"
#include "vec2.hpp"
#include "consts.hpp"


using namespace std;

struct Model {
    vector<Ball> balls;

    Model() : balls(vector<Ball>()) {
        for (int i = 0; 20 > i; i++ ) {
            this->balls.push_back(
             Ball(
                 Vec2((float)(rand()%(int)WINDOW_WIDTH),(float)(rand()%(int)WINDOW_HEIGHT)),
                 Vec2((float)(rand()%120-60),(float)(rand()%120-60)),
                 (float)(rand()%15+5)
             )
         );
        }
    }
};

#endif // MODEL_HPP_GUARD

