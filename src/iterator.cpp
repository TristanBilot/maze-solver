#include <assert.h>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>
#include <memory>
#include <cmath>
#include <vector>
#include <exception>
#include <string.h>
#include "include/fields.hpp"
#include "include/iterator.hpp"

box_iterator::box_iterator(coord x_beg, coord x_end,
				coord y_beg, coord y_end) : x_beg_(x_beg), x_end_{x_end}, y_beg_{y_beg}, y_end_{y_end}, c_pos_{point2d(x_beg, y_beg)}
{
}
// todo

// todo possible other ctors for convenience

box_iterator::box_iterator(const point2d &lower_left, const point2d &upper_right) : x_beg_(lower_left.x), x_end_(upper_right.x), y_beg_{lower_left.y}, y_end_{upper_right.y}, c_pos_{lower_left} {}
// todo
// Create the box from the lower_left corner (belongs to the box)
// and the upper_right corner (just outside the box)

// todo possible others for convenience

void box_iterator::reset()
{
	c_pos_.x = x_beg_;
	c_pos_.y = y_beg_;
}

//doesn't work with negative values
box_iterator &box_iterator::operator++()
{
	c_pos_.x++;
	if (c_pos_.x == x_end_)
	{
		c_pos_.y++;
		if (c_pos_.y < (y_end_))
			c_pos_.x = x_beg_;
	}
	return *this;
}

bool box_iterator::operator==(const box_iterator &o) const
{
	return x_beg_ == o.x_beg_ && x_end_ == o.x_end_ && y_end_ == o.y_end_ && y_beg_ == o.y_beg_ && c_pos_ == o.c_pos_;
}

bool box_iterator::operator!=(const box_iterator &o) const
{
	return x_beg_ != o.x_beg_ || x_end_ != o.x_end_ || y_end_ != o.y_end_ || y_beg_ != o.y_beg_ || c_pos_ != o.c_pos_;
}

//   // Dereference : use the operator*() to generate a point
//   // from current iterator
point2d box_iterator::operator*() const
{
	return c_pos_;
}

//   // Convenience functions
point2d box_iterator::get_c_pos() const
{
	return c_pos_;
}
//   // is_done returns true if the current positions
//   // corresponds to the end position
bool box_iterator::is_done() const
{
	return c_pos_.x == x_end_ && c_pos_.y == y_end_;
}

maze_iterator::maze_iterator( coord x_beg,  coord x_end,  coord y_beg,  coord y_end,
		point2d c_pos, const maze_storage* ms) : box_iterator(0,0,0,0)
{
	coord max = ms->max_coord();
	x_beg_ = x_beg >= 0 ? x_beg : 0;
	x_end_ = x_end <= max ? x_end : max;
	y_beg_ = y_beg >= 0 ? y_beg : 0;
	y_end_ = y_end <= max ? y_end : max;

	c_pos_ = c_pos;
	if (c_pos.x < 0)
		c_pos_.x = 0;
	else if (c_pos.x > max)
		c_pos_.x = max;
	if (c_pos.y < 0)
		c_pos_.y = 0;
	else if (c_pos.y > max)
		c_pos_.y = max;

	ms_ = ms;
}

bool maze_iterator::operator==(const maze_iterator& o) const
{
	return x_beg_ == o.x_beg_ && x_end_ == o.x_end_ && y_end_ == o.y_end_ && y_beg_ == o.y_beg_ && c_pos_ == o.c_pos_ && ms_ == o.ms_;
}

bool maze_iterator::operator!=(const maze_iterator& o) const
{
	return x_beg_ != o.x_beg_ || x_end_ != o.x_end_ || y_end_ != o.y_end_ || y_beg_ != o.y_beg_ || c_pos_ != o.c_pos_ || ms_ != o.ms_;
}

maze_iterator& maze_iterator::operator++()
{
	c_pos_.x++;
	if (c_pos_.x == x_end_)
	{
		c_pos_.y++;
		if (c_pos_.y < (y_end_))
			c_pos_.x = x_beg_;
	}
	return *this;
}

std::pair<point2d, field_ptr> maze_iterator::operator*() const
{
	std::pair<point2d, field_ptr> ret(c_pos_, (*ms_)(c_pos_));
	return ret;
}
