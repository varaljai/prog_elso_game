#include "graphics.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ball.hpp"
#include "consts.hpp"
#include "model.hpp"

using namespace genv;
using namespace std;

void clear() {
    gout << move_to(0, 0);
    gout << color(25, 23, 36);
    gout << box_to(WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
}

enum GameState {
    MainMenu,
    Game,
    EndScreen,
};

struct App {
private:
    Model model;
    GameState game_state;
    bool victory;

public:
    App() : model(Model()), game_state(MainMenu), victory(false) {
        srand(time(0));
        gout.open(WINDOW_WIDTH, WINDOW_HEIGHT);
        gout << font("LiberationSans-Regular.ttf", 20);
        gout << refresh;
        gin.timer(FRAME_TIME);
    }

    void event_main_menu(const event &ev) {
        if (ev.type == ev_key && ev.keycode == key_enter) {
            this->game_state = Game;
            this->model = Model();
        }
    }

    void event_game(const event &ev) {
        if (ev.type == ev_timer) {
            float dt = (float)FRAME_TIME / 1000.;

            for (int i = 0; i < this->model.balls.size(); i++) {
                Ball &a_ball = this->model.balls[i];
                a_ball.update(dt);

                for (int j = i + 1; j < this->model.balls.size(); j++) {
                    Ball &b_ball = this->model.balls[j];
                    a_ball.check_collision_with_a_ball_and_resolve(b_ball);
                }

                Vec2 normal(0., 0.), closest(0., 0.);
                if (a_ball.check_collision_with_block(&this->model.paddle, normal, closest)) {
                    Vec2 paddle_pos = this->model.paddle.get_position();
                    paddle_pos.y += PADDLE_WIDTH / 2.0;
                    a_ball.paddled(paddle_pos);
                }

                for (int j = 0; j < this->model.blocks.size(); j++) {
                    Block *block = this->model.blocks[j];
                    if (a_ball.check_collision_with_block(block, normal, closest)) {
                        a_ball.block_hit(normal);
                        if (block->hit() == SpawnBall) {
                            this->model.balls.push_back(Ball(this->model.paddle.get_position()));
                        }
                    }
                }
            }

            this->model.paddle.update(dt);

            erase_if(this->model.blocks, [](Block* block) { return block->get_is_marked_for_remove(); });
            erase_if(this->model.balls, [](Ball ball) { return ball.get_is_marked_for_remove(); });

            if (this->model.blocks.empty()) {
                this->victory = true;
                this->game_state = EndScreen;
            } else if (this->model.balls.empty()) {
                this->victory = false;
                this->game_state = EndScreen;
            }
        }
        else if (ev.type == ev_key) {
            if (ev.keycode == key_left) this->model.paddle.move_to_left = true;
            else if (ev.keycode == -key_left) this->model.paddle.move_to_left = false;
            if (ev.keycode == key_right) this->model.paddle.move_to_right = true;
            else if (ev.keycode == -key_right) this->model.paddle.move_to_right = false;
        }
    }

    void event_end_screen(const event &ev) {
        if (ev.type == ev_key && ev.keycode == key_enter) {
            this->game_state = MainMenu;
        }
    }

    void draw_main_menu() {
        string t1 = "BRICK BREAKER";
        string t2 = "Press ENTER to Start";
        string t3 = "Press ESC to Exit";

        gout << color(224, 222, 244);
        gout << move_to(WINDOW_WIDTH/2 - gout.twidth(t1)/2, WINDOW_HEIGHT/2 - 40) << text(t1);
        gout << move_to(WINDOW_WIDTH/2 - gout.twidth(t2)/2, WINDOW_HEIGHT/2 + 10) << text(t2);
        gout << move_to(WINDOW_WIDTH/2 - gout.twidth(t3)/2, WINDOW_HEIGHT/2 + 40) << text(t3);
    }

    void draw_game() {
        for (Ball ball : this->model.balls) ball.draw();
        this->model.paddle.draw();
        for (Block *block : this->model.blocks) block->draw();
    }

    void draw_end_screen() {
        string msg = victory ? "VICTORY!" : "GAME OVER";
        string sub = "Press Enter to return to Menu";

        gout << color(victory ? color(100, 255, 100) : color(255, 100, 100));
        gout << move_to(WINDOW_WIDTH/2 - gout.twidth(msg)/2, WINDOW_HEIGHT/2 - 10) << text(msg);
        gout << color(224, 222, 244);
        gout << move_to(WINDOW_WIDTH/2 - gout.twidth(sub)/2, WINDOW_HEIGHT/2 + 30) << text(sub);
    }

    void event(const event &ev) {
        switch (this->game_state) {
            case MainMenu:
                event_main_menu(ev);
                break;
            case Game:
                event_game(ev);
                break;
            case EndScreen:
                event_end_screen(ev);
                break;
        }
    }

    void draw() {
        clear();
        switch (this->game_state) {
            case MainMenu:
                draw_main_menu();
                break;
            case Game:
                draw_game();
                break;
            case EndScreen:
                draw_end_screen();
                break;
        }
        gout << refresh;
    }
};

int main() {
    App app;
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        app.event(ev);
        if (ev.type == ev_timer) {
            app.draw();
        }
    }
    return 0;
}