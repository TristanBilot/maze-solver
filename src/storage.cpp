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

#include "include/storage.hpp"
#include "include/fields.hpp"
#include "include/iterator.hpp"



// n is expected to be the total number of elements,
// not the number of rows/cols
// If n != (std::sqrt(n))*(std::sqrt(n))
// a runtime_error has to be thrown
template <class T>
storage<T>::storage(size_t n)
{
	if (n != (std::sqrt(n)) * (std::sqrt(n)))
		throw std::runtime_error("Runtime error");
	if (n == 0)
	{
		this->nb_elm = 0;
		board = new T*[1];
		for (int i = 0; i < 1; ++i) {
			board[i] = new T[1];
		}
	}
	else
	{
		this->nb_elm = n;

		int row = std::sqrt(n);
		board = new T*[row];
		for (int i = 0; i < row; ++i) {
			board[i] = new T[row];
			for (int j = 0; j < row; j++)
			{
				board[i][j] = 0;
			}
		}
	}
}

// Accessing a point outside of the
// storage has to throw an exception
// Use operator() to acces elements
// We need a const and a non-const version
// todo
template <class T>
T &storage<T>::operator()(const point2d &p) const
{
	if (!has_point(p))
		throw std::runtime_error("Runtime error");
	return board[(int)p.x][(int)p.y];
}

template <class T>
T &storage<T>::operator()(const point2d &p)
{
	if (!has_point(p))
		throw std::runtime_error("Runtime error");
	return board[(int)p.x][(int)p.y];
}

template <class T>
coord storage<T>::max_coord() const
{
	return std::sqrt(nb_elm);
}

template <class T>
coord storage<T>::max_coord()
{
	return std::sqrt(nb_elm);
}

// todo

// Check if a given point exists within this representation
template <class T>
bool storage<T>::has_point(const point2d &p) const
{
	return (p.x >= 0 && p.x < max_coord()) && (p.y >= 0 && p.y < max_coord());
}
// todo

// This function should RESERVE (like the function for std::vector)
// at least n elements (and verify that it is still a square matrix)
template <class T>
void storage<T>::reserve(unsigned n)
{
	while (n != (std::sqrt(n)) * (std::sqrt(n)))
	{
		n++;
	}
	if (n > nb_elm)
	{
		int row = std::sqrt(n);
		T **newBoard = new T*[row];
		for (int i = 0; i < row; ++i) {
			newBoard[i] = new T[row];
			for (int j = 0; j < row; j++)
			{
				newBoard[i][j] = 0;
			}
		}
		memcpy(newBoard, board, row);
		board = new T*[row];
		for (int i = 0; i < row; ++i) {
			board[i] = new T[row];
			for (int j = 0; j < row; j++)
			{
				board[i][j] = 0;
			}
		}
		memcpy(board, newBoard, row);

		for (int i = 0; i < row; i++)
		{
			delete [] newBoard[i];
		}
		delete [] newBoard;
		nb_elm = n;
	}
}

// todo

// This function should RESIZE (like the function for std::vector)
// the storage to hold at least n elements
// (and verify that it is still a square matrix)
template <class T>
void storage<T>::resize(unsigned n)
{
	while (n != (std::sqrt(n)) * (std::sqrt(n)))
	{
		n++;
	}
	int row = std::sqrt(n);
	T **newBoard = new T*[row];
	for (int i = 0; i < row; ++i) {
		newBoard[i] = new T[row];
		for (int j = 0; j < row; j++)
		{
			newBoard[i][j] = 0;
		}
	}
	memcpy(newBoard, board, row);
	board = new T*[row];
	for (int i = 0; i < row; ++i) {
		board[i] = new T[row];
		for (int j = 0; j < row; j++)
		{
			board[i][j] = 0;
		}
	}
	memcpy(board, newBoard, row);

	for (int i = 0; i < row; i++)
	{
		delete [] newBoard[i];
	}
	delete [] newBoard;
	nb_elm = n;
}
// Convenience accessor
template <class T>
T**& storage<T>::get_storage() { return board; }


maze::maze(const std::string &str) : maze_storage(str.length()) {
	int n = str.length();
	std::cout << "length of n : " << n << std::endl;
	for (int i = 0; i < n; i++) {
		if (str[i] == 'I')
			spawn_ = {(coord) ((int) (fmod(i, sqrt(n)))), (coord) ((int) (i / (int)sqrt(n)))};

		int x = i / sqrt(n);
		int y = fmod(i, sqrt(n));
		board[y][x] = to_field(str[i]);
	}
}

maze_iterator maze::begin() const {
	return maze_iterator(this);
}
// todo

maze_iterator maze::end() const {
	maze_iterator end = maze_iterator(this);
	while (!end.is_done())
		++end;
	return end;
}
// todo
// iterating from begin() to end() has to span the whole maze

std::pair<maze_iterator, maze_iterator>
maze::get_box_iterator(const point2d& p_beg, const point2d& p_end) const {
	maze_iterator begin = maze_iterator(p_beg.x, p_end.x, p_beg.y, p_end.y, p_beg, this);
	maze_iterator end = maze_iterator(p_beg.x, p_end.x, p_beg.y, p_end.y, p_end, this);
	std::pair<maze_iterator, maze_iterator> its(begin, end);
	return its;
}
//Iterate over a box within the maze

point2d maze::get_entrance_pos() const {
	return spawn_;
}
// This one might be useful but is not tested

field_effect maze::accum_effects(const point2d& c_pos, bool is_sim) const {
	field_effect acc;
	std::pair<maze_iterator, maze_iterator> its = get_box_iterator(c_pos - offset2d(1, 1), c_pos + offset2d(2, 2));
	maze_iterator begin = its.first;
	while (!begin.is_done())
	{
		acc += ((*begin).second)->effect((*begin).first - c_pos, is_sim);
		++begin;
	}
	return acc;
}

std::pair<maze_iterator, maze_iterator>
maze::observe_maze(const point2d& p) const {
	return get_box_iterator(p - offset2d(2, 2), p + offset2d(3, 3));
}

template class storage<int>;
template class storage<field_ptr>;

