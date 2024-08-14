#pragma once
#include <graphics.h>

#include "Animation.h"
#include "vector2.h"
#include "ID.h"
#include "functional"

#pragma comment(lib, "winmm.lib")

using namespace std;

class Bullet
{
public:
	Bullet() {};
	~Bullet() {};

public:
	void set_damage(int val) 
	{ 
		damage = val;
	}
	int get_damage() const
	{
		return damage; 
	}
	void set_position(float x, float y) 
	{ 
		position.x = x; position.y = y; 
	}
	const vector2& get_position()
	{ 
		return position;
	}
	const vector2& get_size() const
	{ 
		return size; 
	}
	void set_velocity(float x, float y) 
	{ 
		velocity.x = x; velocity.y = y;
	}
	void set_collide_target(const ID& id)
	{ 
		target_id = id;
	}
	ID get_collide_target() const
	{ 
		return target_id;
	}
	void set_callback(function<void()> callback)
	{ 
		this->callback = callback; 
	}
	void set_valid(bool val) 
	{ 
		valid = val;
	}
	bool get_valid() const
	{ 
		return valid;
	}
	bool check_can_remove() const
	{
		return can_remove;
	}

	virtual void on_collide() 
	{
		if (callback)
			callback();
	};
	virtual bool check_collide(const vector2& position, const vector2& size)
	{
		return this->position.x + size.x / 2 >= position.x
			&& this->position.x + size.x / 2 <= position.x + size.x
			&& this->position.y + size.y / 2 >= position.y
			&& this->position.y + size.y / 2 <= position.y + size.y;
	}
	virtual void on_update(int delta) {};
	virtual void on_draw(const Camera& camera) {};

protected:
	bool check_if_exceeds_screen() const
	{
		return position.x < -size.x - 1 || position.x > 1281
			|| position.y < -size.y - 1 || position.y  > 721;
	}

protected:
	vector2 size;
	vector2 position;
	vector2 velocity;
	int damage;
	bool valid = true;
	bool can_remove = false;
	function<void()>callback;
	ID target_id;
};