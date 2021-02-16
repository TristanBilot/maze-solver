#include <termios.h>
#include <unistd.h>
#include <utility>
#include "include/game.hpp"
#include<unistd.h>

ai_game::ai_game(const std::string &str, size_t length) :
    game(),
    maze_(maze(str)),
    player_(AIplayer("player", length))
    { }

void ai_game::start_game() {
    std::cout << INSTRUCTION;
    point2d entrance = maze_.get_entrance_pos();
    player_.set_pos(entrance);
    update_user_area(entrance);

    render_maze(&maze_, &player_);
    while (player_.get_life() == life::ALIVE)
    {
        display_user_hp(&player_);
        usleep(AI_SPEED);

        point2d newPos = player_.solve();
        update_user_area(newPos);
        field_effect effect = maze_.accum_effects(newPos, true);

        update_user_position(&effect, &player_, &newPos);
        render_maze(&maze_, &player_);
    }
}

void ai_game::update_user_area(point2d newPos) {
    player_visible_area area = {
        .current = maze_.accum_effects(newPos, true),
        .up = maze_.accum_effects(player_.get_pos_with_offset(newPos, orientation::UP), true),
        .right = maze_.accum_effects(player_.get_pos_with_offset(newPos, orientation::RIGHT), true),
        .down = maze_.accum_effects(player_.get_pos_with_offset(newPos, orientation::DOWN), true),
        .left = maze_.accum_effects(player_.get_pos_with_offset(newPos, orientation::LEFT), true)
    };
    player_.set_visible_area(area);
}
