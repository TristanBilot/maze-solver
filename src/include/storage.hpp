#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <utility>
#include <iostream>
#include "fields.hpp"

template <class T>
class storage
{
public:
	storage() = delete;
	~storage() {}
	explicit storage(size_t n);

	storage(const storage &other) = default;
	storage &operator=(const storage &other) = default;

	T &operator()(const point2d &p) const;
	T &operator()(const point2d &p);

	coord max_coord() const;
	coord max_coord();

	bool has_point(const point2d &p) const;
	void reserve(unsigned n);
	void resize(unsigned n);
	T**& get_storage();
	void set_storage(int &x, int &y, const T &value) {
		board[x][y] = value;
	}

protected:
	// todo
	size_t nb_elm;
	T **board;
};

// using maze_storage = storage<field_ptr>;

class maze_iterator;

class maze : public storage<field_ptr>
{
public:
	maze(const std::string &str);
	maze_iterator begin() const;
	maze_iterator end() const;
	std::pair<maze_iterator, maze_iterator> get_box_iterator(const point2d& p_beg, const point2d& p_end) const;
	point2d get_entrance_pos() const;
	field_effect accum_effects(const point2d& c_pos, bool is_sim) const;
	std::pair<maze_iterator, maze_iterator> observe_maze(const point2d& p) const;

private:
	point2d spawn_ = {1, 1};
};

#endif /* STORAGE_HPP */
