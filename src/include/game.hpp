#ifndef GAME_HPP
#define GAME_HPP

#include "storage.hpp"
#include "player.hpp"
#include "iterator.hpp"

#define AI_SPEED 0.2 * 1000000 /* 0.2 sec */

#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

#define INSTRUCTION "I: entrance, O: exit, P: courrent position, w: wall\nt: small trap, T: large trap\nX: fog-of-war\nwhite space is walk-able region\n"
#define COMMANDS "w:up, s:down, a:left, d:right\n"

#define DIED "YOU DIED."
#define WIN "YOU WON!"

#define MOVE_OK "MOVE SUCCEED"
#define MOVE_NOK "MOVE FAILED"

using bool_storage = storage<bool>;

class game
{
public:
    game() = default;
    virtual void start_game() = 0;
    virtual ~game() = default;

protected:
    void update_user_position(field_effect *effect, player *player_, point2d *newPos);
    void display_user_hp(player *player_);
    void render_maze(maze *maze_, player *player_);
};

class manual_game: public game
{
public:
    manual_game(const std::string &str, size_t length);
    void start_game() override;

private:
    maze maze_;
    player player_;

    point2d handle_arrow_keys();
};

class ai_game: public game
{
public:
    ai_game(const std::string &str, size_t length);
    void start_game() override;

private:
    maze maze_;
    AIplayer player_;

    void update_user_area(point2d newPos);
};

#endif