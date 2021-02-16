#include "include/game.hpp"

void game::update_user_position(field_effect *effect, player *player_, point2d *newPos) {
    std::cout << std::endl;
    if (effect->state == field_state::BLOCKED)
        std::cout << MOVE_NOK << std::endl;
    else if (effect->damage > 0) {
        std::cout << MOVE_OK << std::endl;
        player_->set_pos(*newPos);
        player_->lose_hp(effect->damage);
    }
    else if (effect->state == field_state::FREE) {
        std::cout << MOVE_OK << std::endl;
        player_->set_pos(*newPos);
    }
    else if (effect->state == field_state::ENTRANCE) {
        std::cout << MOVE_OK << std::endl;
        player_->set_pos(*newPos);
    }
    else if (effect->state == field_state::EXIT) {
        std::cout << GREEN << WIN << std::endl << RESET;
        player_->set_life(life::WON);
    }
    if (effect->state == field_state::DEADLY || player_->get_hp() == 0) {
        std::cout << RED << DIED << std::endl << RESET;
        player_->set_life(life::DEAD);
    }
}

void game::display_user_hp(player *player_) {
    std::cout << "============================================================" << std::endl;
    std::cout << "PLAYER : " << player_->name_ << std::endl;
    std::cout << "HP : " << player_->get_hp() << std::endl << std::endl;
}

void game::render_maze(maze *maze_, player *player_) {
    std::pair<maze_iterator, maze_iterator> its = maze_->observe_maze(player_->get_pos());
    player_->observation(its);
}
