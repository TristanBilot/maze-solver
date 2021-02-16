#include <termios.h>
#include <unistd.h>
#include <utility>
#include "include/game.hpp"

manual_game::manual_game(const std::string &str, size_t length) :
    game(),
    maze_(maze(str)),
    player_(manual("player", length))
    { }

void manual_game::start_game() {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    std::cout << INSTRUCTION;
    point2d entrance = maze_.get_entrance_pos();
    std::cout << "point x : " << entrance.x << " et point y  : " << entrance.x << std::endl;
    player_.set_pos(entrance);
    while (player_.get_life() == life::ALIVE)
    {
        display_user_hp(&player_);
        render_maze(&maze_, &player_);

        std::cout << COMMANDS;
        point2d newPos = handle_arrow_keys();
        field_effect effect = maze_.accum_effects(newPos, false);
        
        update_user_position(&effect, &player_, &newPos);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

point2d manual_game::handle_arrow_keys() {
    int c = 0;
    switch ((c = getchar()))
    {
    case KEY_UP:
        return player_.move(orientation::UP);
    case KEY_DOWN:
        return player_.move(orientation::DOWN);
    case KEY_LEFT:
        return player_.move(orientation::LEFT);
    case KEY_RIGHT:
        return player_.move(orientation::RIGHT);
    default:
        break;
    }
    return point2d(0,0);
}
