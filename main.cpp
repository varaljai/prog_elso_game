#include "graphics.hpp"
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iostream>
#include "ball.hpp"
#include "consts.hpp"
#include "model.hpp"


using namespace genv;
using namespace std;

void clear() {
    gout << move_to(0, 0);
    gout << color(25, 23, 36);
    gout << box_to(WINDOW_WIDTH-1.,WINDOW_HEIGHT-1.);
}



struct App {
private:
    Model model;

public:
    App() : model(Model()) {
        srand(time(0));
        gout.open(WINDOW_WIDTH,WINDOW_HEIGHT);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << refresh;
        gin.timer(FRAME_TIME);

    }

    void event(const event &ev) {
        if (ev.type == ev_timer) {
            float dt = (float)FRAME_TIME /1000.; // TODO: el lehet-e kérni az eltelt időt?
            for (int i=0; this->model.balls.size() > i; i++) {
                Ball &a_ball = this->model.balls[i];
                a_ball.update(dt);

                for (int j = i+1; this->model.balls.size() > j; j++) {
                    Ball &b_ball = this->model.balls[j];
                    a_ball.check_collision_with_a_ball_and_resolve(b_ball);
                }
                Vec2 normal = Vec2(0.,0.);
                Vec2 closest = Vec2(0.,0.);
                if (a_ball.check_collision_with_block(&this->model.paddle,normal, closest)) {
                    Vec2 paddle_pos = this->model.paddle.get_position();
                    paddle_pos.y += PADDLE_WIDTH / 2.;
                    a_ball.paddled(paddle_pos);
                }
                for (int j = 0; this->model.blocks.size() > j; j++) {
                    Block *block = this->model.blocks[j];
                    if (a_ball.check_collision_with_block(block, normal, closest)) {
                        a_ball.block_hit(normal);
                        switch (block->hit()) {
                            case DoNothing:
                                break;
                            case SpawnBall:
                                this->model.balls.push_back(Ball(this->model.paddle.get_position()));
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
            this->model.paddle.update(dt);
            std::erase_if(this->model.blocks, [](Block* block) {
                if (block->get_is_marked_for_remove()) {
                    delete block;
                    return true;
                }
                return false;
            });
            std::erase_if(this->model.balls, [](Ball ball) {return ball.get_is_marked_for_remove();});

        }
        else if (ev.type == ev_key) {
            if (ev.keycode == key_left) {
                this->model.paddle.move_to_left = true;
            }
            else if (ev.keycode == -key_left) {
                this->model.paddle.move_to_left = false;
            }
            if (ev.keycode == key_right) {
                this->model.paddle.move_to_right = true;
            }
            else if (ev.keycode == -key_right) {
                this->model.paddle.move_to_right = false;
            }
        }
    }

    void draw() {
        clear();

        for (Ball ball : this->model.balls) {
            ball.draw();
        }
        this->model.paddle.draw();
        for (Block *block : this->model.blocks) {
            block->draw();
        }

        gout << refresh;
    }

};

int main() {
    App app = App();
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        app.event(ev);
        if (ev.type == ev_timer) {
            app.draw();
        }
    }
    return 0;
}
