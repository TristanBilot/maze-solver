#include <assert.h>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>

#include "include/coordinates.hpp"

offset2d::offset2d(coord dx_in, coord dy_in)
{
	this->dx = dx_in;
	this->dy = dy_in;
}

bool offset2d::operator==(const offset2d &o) const
{
	return this->dx == o.dx && this->dy == o.dy;
}

bool offset2d::operator!=(const offset2d &o) const
{
	return this->dx != o.dx || this->dy != o.dy;
}

bool offset2d::operator<(const offset2d &o) const
{
	return this->dx < o.dx && this->dy < o.dy;
}

offset2d& offset2d::operator+=(const offset2d &o)
{
	dx += o.dx;
	dy += o.dy;
	return *this;
}

offset2d& offset2d::operator-=(const offset2d &o)
{
	dx -= o.dx;
	dy -= o.dy;
	return *this;
}
offset2d offset2d::operator+(const offset2d &other) const
{
	return offset2d(this->dx + other.dx, this->dy + other.dy);
}
offset2d offset2d::operator-(const offset2d &other) const
{
	return offset2d(this->dx - other.dx, this->dy - other.dy);
}


void offset2d::toString(void)
{
	std::cout << "Les coordonée du offset:  x : " << this->dx;
	std::cout << "  et  y : " << this->dy << std::endl;
}


point2d::point2d(coord x_in, coord y_in)
{
	this->x = x_in;
	this->y = y_in;
}


bool point2d::operator==(const point2d &o) const
{
	return this->x == o.x && this->y == o.y;
}
bool point2d::operator!=(const point2d &o) const
{
	return this->x != o.x || this->y != o.y;
}
bool point2d::operator<(const point2d &o) const
{
	return this->x < o.x && this->y < o.y;
}
point2d& point2d::operator+=(const offset2d &o)
{
	x += o.dx;
	y += o.dy;
	return *this;
}
point2d& point2d::operator-=(const offset2d &o)
{
	x -= o.dx;
	y -= o.dy;
	return *this;
}

void point2d::toString(void)
{
	std::cout << "Les coordonnées des point2d de x : " << this->x;
	std::cout << "  et  y : " << this->y << std::endl;
}
// todo : Implement the functions corresponding to
// these signatures

point2d operator+(const point2d &p, const offset2d &o)
{
	return point2d(p.x + o.dx, p.y + o.dy);
}

point2d operator+(const offset2d &o, const point2d &p)
{
	return point2d(p.x + o.dx, p.y + o.dy);
}

point2d operator-(const point2d &p, const offset2d &o)
{
	return point2d(p.x - o.dx, p.y - o.dy);
}
point2d operator-(const offset2d &o, const point2d &p)
{
	return point2d(o.dx - p.x, o.dy - p.y);
}

offset2d operator-(const point2d &p1, const point2d &p2)
{
	return offset2d(p1.x - p2.x, p1.y - p2.y);
}

namespace std {
	template<> struct less<offset2d>
	{
		bool operator()(const offset2d &a, const offset2d &b) const { return a < b; }
		// todo : Look up where std::less is used,
		// then implement it
	};
}

namespace std {
	template<> struct less<point2d>
	{
		bool operator()(const point2d &a, const point2d &b) const { return a < b; }
		// todo : Look up where std::less is used,
		// then implement it
	};
}



// int main()			/* Test des structures */
// {
// 	offset2d a = offset2d(2,3);
// 	offset2d b = offset2d(4,1);
// 	offset2d c = offset2d(2,-2);

// 	a.toString();
// 	b.toString();
// 	c.toString();

// 	assert(a != b); // "offsets should not be equal"
// 	assert(a == a); // "an offset should be equal to itself"
// 	assert(b == b); // "an offset should be equal to itself"
// 	assert(b == a + c); // "offsets should be equal if the coordinates are the same"
// 	assert(a == b - c); // "offsets should be equal if the coordinates are the same"
// 	assert((a += b) == offset2d(6, 4)); // "an offset incrementation should be equal to the sum of the coordinates"
// 	assert((offset2d(6,4) -= offset2d(3, 2)) == offset2d(3, 2)); // "an offset incrementation should be equal to the sum of the coordinates"



// 	/* Points test */
// 	point2d d = point2d(2,3);
// 	point2d e = point2d(4,1);
// 	point2d f = point2d(2,-2);

// 	d.toString();
// 	e.toString();
// 	f.toString();

// 	assert(d != e); // "points should not be equal"
// 	assert(d == d); // "an point should be equal to itself"
// 	assert(e == e); // "an point should be equal to itself"
// 	assert((point2d(3,2)+= offset2d(3,2)) == point2d(6, 4)); // "an point incrementation should be equal to the sum of the coordinates"
// 	assert((offset2d(6,4) -= offset2d(3, 2)) == offset2d(3, 2)); // "an point incrementation should be equal to the sum of the coordinates"

// 	/* Function not in class */
// 	assert(d + offset2d(2,3) == point2d(4,6)); // "check if addition of point and an offset is equal to a point "
// 	assert(offset2d(2,3) + d == point2d(4,6)); // "check if addition of an offset and a point is equal to a point "
// 	assert(e - offset2d(2, 1) == point2d(2,0)); // "check if a point minus an offset is equal to a point2d"
// 	assert(offset2d(4, 6) - d == point2d(2,3)); // "check if an offset minus a point is equal to a point2d"
// 	assert(e - point2d(2, 1) == offset2d(2,0)); // "check if a point minus a point is equal to a offset"


// 	point2d g = point2d(-2,-3);
// 	point2d h = point2d(0,0);
// 	point2d i = point2d(2,2);

// 	std::list<point2d> pointList;
// 	pointList.push_back(h);
// 	pointList.push_back(i);
// 	pointList.push_back(g);
// 	std::list<point2d> resList;
// 	resList.push_back(g);
// 	resList.push_back(h);
// 	resList.push_back(i);
// 	pointList.sort(std::less<point2d>());
// 	assert(pointList== resList);
// 	return 0;
// }