#pragma once
#include "Camera.h"
#include "util.h"
#include "vector2.h"
#include "Animation.h"
#include "ID.h"

class Player
{
public:
	Player();
	~Player();

public:
	virtual void on_start();

	virtual void on_update(int delta);
	virtual void on_draw(const Camera& camera);
	virtual void on_input(const ExMessage& msg);
	virtual void set_id(ID id);
	virtual void set_position(float x, float y);

protected:
	virtual void on_run(float diatance);
	virtual void on_jump();
	virtual void on_attack();
	virtual void on_attack_ex();

protected:
	void move_and_collide(int delta);

public:
	void set_hp(int val);

public:
	const vector2& get_position();
	const vector2& get_size();
	int get_hp() const;
	int get_mp() const;
protected:
	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;

	const float run_speed = 0.55f;
	const float gravity = 1.6e-3f;
	const float jump_speed = -0.75f;

protected:
	int mp = 10;
	int hp = 300;
	int attack_cd;
	bool is_facing_right;
	bool is_attacking_ex = false;
	vector2 position;
	vector2 size;
	ID id;
	

private:
	
	vector2 velocity;

	Animation* current_animation = nullptr;

	bool is_left_keydown = false;
	bool is_right_keydown = false;

	bool can_attack = true;
	Timer timer_attack_cd;
};

