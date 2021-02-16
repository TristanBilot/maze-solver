#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "coordinates.hpp"
#include "storage.hpp"
 
class box_iterator
{
public:
	// The following is not strictly necessary for our code
	// however if you want to have an iterator confirming to the
	// c++ standard you need this.
	using iterator_category = std::forward_iterator_tag;
	using value_type = point2d;
	//   // Has no sense for forward iterators but must be specified for
	//   // certain platforms in order to compile (g++ for instance)
	using difference_type = void;
	using pointer = point2d *;
	using reference = point2d &;

	box_iterator(coord x_beg, coord x_end,
				 coord y_beg, coord y_end);

	box_iterator(const point2d &lower_left, const point2d &upper_right);
	// todo
	// Create the box from the lower_left corner (belongs to the box)
	// and the upper_right corner (just outside the box)

	// todo possible others for convenience

	void reset();

	box_iterator &operator++();

	bool operator==(const box_iterator &o) const;

	bool operator!=(const box_iterator &o) const;

	//   // Dereference : use the operator*() to generate a point
	//   // from current iterator
	point2d operator*() const;
	//box_points.insert(*b);

	//   // Convenience functions
	point2d get_c_pos() const;
	//   // is_done returns true if the current positions
	//   // corresponds to the end position
	bool is_done() const;

protected:
	coord x_beg_,
		x_end_,
		y_beg_,
		y_end_;
	point2d c_pos_;
};

using maze_storage = storage<field_ptr>;

class maze_iterator : public box_iterator
{
public:
	maze_iterator() = delete;
	// Note that the pointer passed as argument is NON-OWNING
	// an has to exist at least as long as the iterator
	maze_iterator(const maze_storage* ms) : box_iterator(point2d(0, 0), point2d(ms->max_coord(), ms->max_coord())), ms_{ms} {}

	// Without further info, the maze_iterator iterates over the entire maze
	// todo


	maze_iterator( coord x_beg,  coord x_end,  coord y_beg,  coord y_end,
			point2d c_pos, const maze_storage* ms);
	// Here we want to respect the box
	// todo

	maze_iterator(const maze_iterator& other) = default;
	maze_iterator& operator=(const maze_iterator& other) = default;


	bool operator==(const maze_iterator& o) const;

	bool operator!=(const maze_iterator& o) const;

	maze_iterator& operator++();

	std::pair<point2d, field_ptr> operator*() const;

private:
	//
	const maze_storage* ms_;
	// Maybe a private helper function?
};


class neighbour_iterator : public box_iterator
{
public:
    neighbour_iterator(coord x_beg, coord x_end,
				 coord y_beg, coord y_end);
private:
	point2d spawn_ = {1, 1};

};

#endif /* ITERATOR_HPP */
