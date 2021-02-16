#include <assert.h>
#include <iostream>
#include <functional>
#include <list>
#include <algorithm>
#include <memory>
#include <cmath>
#include <vector>
#include <exception>


#include "include/fields.hpp"

//include gameplay.cpp


// To properly describe the effects,
// we need to keep track of the (accumulated) damage
// AND the state
// Why is it sufficient to have one member variable of
// type field_state?


field_effect &field_effect::operator+=(const field_effect &other)
{
	if (other.state == field_state::DAMAGING)
		this->damage += other.damage;
	if (other.state > this->state)
		this->state = other.state;
	return *this;
}

bool field_effect::operator!=(const field_effect &other)
{
	return this->state != other.state && this->damage != other.damage;
}


// utils.h stop

//fields.h start
// Base class for all fields
// A field needs to be representable by a char
// (to print the game on the console)
// and we have to be able to evaluate its effects
// a field can effect the cell where it is located, but also surrounding cells.
// To avoid storing a fields own location, we will use the relative distance
// to the cell for which we want to evaluate effect


field_effect field::effect() const
{
	return effect({0, 0});
}

// Note that the constructors for the derived classes do
// not take any argument

maze_entrance::maze_entrance() : field('I')
{
}


field_effect maze_entrance::effect(const offset2d &o, bool is_sim) const
	{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::NONE;
		if (o == offset2d(0, 0))
			field_ef.state = field_state::ENTRANCE;
		(void)o;
		(void)is_sim;
		return field_ef;
	}


maze_exit::maze_exit() : field('O')
	{
	}

field_effect maze_exit::effect(const offset2d &o, bool is_sim) const
	{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::NONE;
		if (o == offset2d(0, 0))
			field_ef.state = field_state::EXIT;
		(void)o;
		(void)is_sim;
		return field_ef;
	}



wall::wall() : field('w')
	{
	}
field_effect wall::effect(const offset2d &o, bool is_sim) const
{
	field_effect field_ef;
	field_ef.damage = 0;
	field_ef.state = field_state::FREE;
	if (o == offset2d(0, 0))
		field_ef.state = field_state::BLOCKED;
	(void)is_sim;
	return field_ef;
}


path::path() : field(' ') {}


field_effect path::effect(const offset2d &o, bool is_sim) const
{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::FREE;
		(void)o;
		(void)is_sim;
		return field_ef;
}

path::~path(){}



small_trap::small_trap() : field('t')
{
}

field_effect small_trap::effect(const offset2d &o, bool is_sim) const
{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::FREE;
		if (o == offset2d(0, 0))
			field_ef.state = field_state::DEADLY;
		(void)is_sim;
		return field_ef;
}

small_trap::~small_trap(){}



large_trap::large_trap() : field('T')
{
}
field_effect large_trap::effect(const offset2d &o, bool is_sim) const
{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::NONE;
		if (o < offset2d(2, 2) && offset2d(-2, -2) < o)
		{
			field_ef.state = field_state::DAMAGING;
			field_ef.damage += rand() % (15 - 5 + 1) + 5;
		}
		(void)is_sim;
		return field_ef;
}
large_trap::~large_trap(){}


hidden_trap::hidden_trap() : field(' ')
{
}

field_effect hidden_trap::effect(const offset2d &o, bool is_sim) const
{
		field_effect field_ef;
		field_ef.damage = 0;
		field_ef.state = field_state::NONE;
		if (!is_sim)
		{
			if (to_char() == 'T')
			{
				if (o < offset2d(2, 2) && offset2d(-2, -2) < o)
				{
					field_ef.state = field_state::DAMAGING;
					field_ef.damage += rand() % (15 - 5 + 1) + 5;
				}
			}
			else if (o == offset2d(0, 0))
			{
				set('T');
				field_ef.damage += rand() % (15 - 5 + 1) + 5;
				field_ef.state = field_state::DAMAGING;
			}
		}
		return field_ef;
}



// A function which converts a char to a shared pointer to a field
// // This function will be useful to generate a maze from a string
field_ptr to_field(char c)
{
	field_ptr a;
	switch (c)
	{
	case ' ':
		a = std::make_shared<path>();
		break;
	case 'T':
		a = std::make_shared<large_trap>();
		break;
	case 't':
		a = std::make_shared<small_trap>();
		break;
	case 'I':
		a = std::make_shared<maze_entrance>();
		break;
	case 'O':
		a = std::make_shared<maze_exit>();
		break;
	case 'w':
		a = std::make_shared<wall>();
		break;
	case 'H':
		a = std::make_shared<hidden_trap>();
		break;
	default:
		a = std::make_shared<path>();
		break;
	}
	return a;
}
