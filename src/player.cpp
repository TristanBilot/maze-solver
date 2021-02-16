#include <utility>
#include <cmath>
#include "include/storage.hpp"
#include "include/player.hpp"
#include "include/iterator.hpp"
// #include "fields.hpp"


player::player(const std::string name, size_t n) : name_(name), states_(maze_storage(n)) {
}

point2d player::move(const orientation &a) {
    return get_pos_with_offset(pos_, a);
}

point2d player::get_pos_with_offset(point2d pos, const orientation &a) {
    switch (a) {
    case orientation::UP:
        return pos + offset2d(0,-1); // l'axe sur x est à l'envers => {0,0} se trouve en haut à gauche
    case orientation::DOWN:
        return pos + offset2d(0,1);
    case orientation::LEFT:
        return pos + offset2d(-1,0);
    case orientation::RIGHT:
        return pos + offset2d(1,0);
    default:
        return pos;
    }
}

void player::observation(std::pair<maze_iterator, maze_iterator> its) {
    maze_iterator begin = its.first;
    maze_iterator end = its.second;
    for (; begin != end; ++begin) {
        int x = ((*begin).first).x;
        int y = ((*begin).first).y;
        states_.set_storage(x, y, (*begin).second);
    }
    box_iterator complete_maze = box_iterator({0, 0}, {states_.max_coord(), states_.max_coord()});
    while(!complete_maze.is_done()) {
        if (*complete_maze == pos_)
            std::cout << 'P';
        else if (states_(*complete_maze) == 0)
            std::cout << 'X';
        else
            std::cout << (*states_(*complete_maze)).to_char();
        ++complete_maze;
        if ((*complete_maze).x == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;

}
