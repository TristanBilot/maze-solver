#ifndef FIELDS_HPP
#define FIELDS_HPP

#include "coordinates.hpp"
#include <memory>

enum class field_state
{
	NONE = 0,
	FREE,
	DAMAGING,
	ENTRANCE,
	EXIT,
	DEADLY,
	BLOCKED,
	VISITED,
};

struct field_effect
{
	field_effect &operator+=(const field_effect &other);

	bool operator!=(const field_effect &other);

	field_state state = field_state::NONE;
	unsigned damage = 0;
};

class field
{
public:
	field(char c)
		: c_{c}
	{
	}

	virtual ~field()
	{
	}

	char to_char() const
	{
		return c_;
	}

	void set(char c) const
	{
		c_ = c;
	}

	bool get_state() const
	{
		return state_;
	}

	void set_state(bool b) const
	{
		state_ = b;
	}

	virtual field_effect effect(const offset2d &o, bool is_sim = true) const = 0;

	field_effect effect() const;

private:
	mutable char c_;
	mutable bool state_ = false;
};



class maze_entrance : public field
{
public:
	maze_entrance();
	field_effect effect(const offset2d &o, bool is_sim) const;
};


class maze_exit : public field
{
public:
	maze_exit();
	field_effect effect(const offset2d &o, bool is_sim) const;
};



class wall : public field
{
public:
	wall();
	field_effect effect(const offset2d &o, bool is_sim = true) const;
};


class path : public field
{
public:
	path();

	field_effect effect(const offset2d &o, bool is_sim) const;

	~path();
};


class small_trap : public field
{
public:
	small_trap();
	field_effect effect(const offset2d &o, bool is_sim) const;
	~small_trap();
};


class large_trap : public field
{
public:
	large_trap();
	field_effect effect(const offset2d &o, bool is_sim) const;
	~large_trap();
};

class hidden_trap : public field
{
public:
	hidden_trap();
	field_effect effect(const offset2d &o, bool is_sim) const;
};


using field_ptr = std::shared_ptr<field>;

field_ptr to_field(char c);

#endif /* FIELDS_HPP */
