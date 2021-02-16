#include "include/player.hpp"
#include "include/fields.hpp"

/*
* DFS-like algorithm to discover all possible paths.
*/
point2d AIplayer::solve() {
    enum orientation next_orient = next_possible_move();
    if (next_orient != orientation::IMPOSSIBLE) {
        /* should apply a real move into the game and update the area */
        visited.insert(std::tuple<int, int>{pos_.x, pos_.y});
        stack.push(pos_);
        return move(next_orient);
    }
    else {
        /* no available path so go back */
        visited.insert(std::tuple<int, int>{pos_.x, pos_.y});
        point2d &back_move = stack.top();
        stack.pop();
        return back_move;
    }
}

enum orientation AIplayer::next_possible_move() {
    std::pair<enum orientation, enum best_move> best = {orientation::IMPOSSIBLE, best_move::IMPOSSIBLE};
    int state = (int) orientation::UP;
    for (; state <= (int) orientation::LEFT; ++state) {
        enum best_move try_orient = should_go_forward(
            get_effect_from_orient(static_cast<enum orientation>(state), area), 
            move(static_cast<enum orientation>(state)));
        if (try_orient == best_move::EXIT)
            return static_cast<enum orientation>(state);
        else if (try_orient > best_move::IMPOSSIBLE && best.second < try_orient) {
            best.first = static_cast<enum orientation>(state);
            best.second = try_orient;
        }
    }
    return best.second == best_move::IMPOSSIBLE ? orientation::IMPOSSIBLE : best.first;
}

enum best_move AIplayer::should_go_forward(field_effect effect, point2d newPos) {
    if (effect.state == field_state::DEADLY || 
        effect.state == field_state::BLOCKED || 
        effect.damage >= hp_ ||
        visited.find(std::tuple<int, int>{newPos.x, newPos.y}) != visited.end())
        return best_move::IMPOSSIBLE;
    if (effect.state == field_state::DAMAGING)
        return best_move::DAMAGING;
    if (effect.state == field_state::FREE)
        return best_move::FREE;
    return best_move::EXIT;
}

field_effect AIplayer::get_effect_from_orient(enum orientation orient, player_visible_area area) {
    switch(orient)
    {
    case orientation::UP:
        return area.up;
    case orientation::RIGHT:
        return area.right;
    case orientation::DOWN:
        return area.down;
    case orientation::LEFT:
        return area.left;
    case orientation::IMPOSSIBLE:
        return area.left;
    }
}

void AIplayer::set_visible_area(const player_visible_area newArea) {
    area = newArea;
}

point2d AIplayer::move(const orientation &a) {
    return player::move(a);
}
