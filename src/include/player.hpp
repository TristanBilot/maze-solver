#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "storage.hpp"
#include <stack>
#include <set>

enum class orientation
{
	UP = 0,
	DOWN,
	RIGHT,
	LEFT,
    IMPOSSIBLE,
};

enum class life
{
    ALIVE = 0,
    DEAD,
    WON,
};

struct player_visible_area {
    field_effect current;
    field_effect up;
    field_effect right;
    field_effect down;
    field_effect left;
};

using maze_storage = storage<field_ptr>;
class player {
public:
    player(const std::string name, size_t n);
    point2d move(const orientation &a);
    point2d get_pos_with_offset(point2d pos, const orientation &a);
    void observation(std::pair<maze_iterator, maze_iterator>);
    unsigned int get_hp() { return hp_; }
    void lose_hp(unsigned int lost_hp) { hp_ = hp_ < lost_hp ? 0 : hp_ - lost_hp; }
    void set_life(const life &l) { life_ = l; }
    life get_life() { return life_; }
    void set_pos(point2d &a) { pos_ = a; }
    point2d &get_pos() { return pos_; }

    std::string name_;

protected:
    unsigned int hp_ = 100;
    point2d pos_ = {1, 1};
    life life_ = life::ALIVE;
    maze_storage states_;
};


class manual : public player {
public:
    manual(std::string name, size_t n) : player(name, n) {};
};

enum class best_move {
    IMPOSSIBLE = 0, /* blocked or died */
    DAMAGING,
    FREE,
    EXIT
};

class AIplayer : public player {
private:
    std::set<std::pair<int, int>> visited;
    std::stack<point2d> stack;
    player_visible_area area;
    
    enum orientation back_move_orient(point2d &curr_point, point2d &prev_point);
    enum best_move should_go_forward(field_effect effect, point2d newPos);
    enum orientation next_possible_move();
public:
    AIplayer(std::string name, size_t n) : player(name, n) {};

    point2d solve();
    point2d move(const orientation &a);
    point2d &get_pos() { return pos_; }
    void set_visible_area(const player_visible_area newrea);
    field_effect get_effect_from_orient(enum orientation orient, player_visible_area area);
};

#endif /* PLAYER_HPP */
