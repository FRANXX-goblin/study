#include "Player.h"
#include "Platform.h"
#include "Bullet.h"
#include <iostream>

extern vector<Platform>platform_list;
extern vector<Bullet*>bullet_list;

Player::Player()
{
	size.x = 96;
	size.y = 96;
}

Player::~Player()
{
}

void Player::on_start()
{
	timer_attack_cd.set_wait_time(attack_cd);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback([&]() {can_attack = true; });
	switch (id)
	{
	case ID::P1:  
		is_facing_right = true;
		set_position(200, 100);
		break;
	case ID::P2:
		is_facing_right = false;
		set_position(975, 100);
		break;
	}
}

void Player::on_update(int delta)
{
	int direction = is_right_keydown - is_left_keydown;
	if (direction != 0)
	{
		
		is_facing_right = direction > 0;
		if (!is_attacking_ex)
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
		else
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		float distance= direction * run_speed * delta;
		on_run(distance); 
	}
	else
	{
		if (!is_attacking_ex)
		current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		else
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
	}
	current_animation->on_update(delta);
	move_and_collide(delta);
	timer_attack_cd.on_update(delta);
}

void Player::on_draw(const Camera& camera)
{
	current_animation->on_draw(camera, (int)position.x, (int)position.y);
}

void Player::on_input(const ExMessage& msg)
{
	switch (id)
	{
	case ID::P1:
		switch (msg.message)
		{
		case WM_KEYDOWN:
		{
			switch (msg.vkcode)
			{
			case 0x41: // A
				is_left_keydown = true;
				break;
			case 0x44: // D
				is_right_keydown = true;
				break;
			case 0x57: // W
				on_jump();
				break;
			case 0X46: // F
				if (can_attack)
				{
					on_attack();
					timer_attack_cd.restart();
					can_attack = false;
				}
				break;
			case 0X47: // G
				if (mp >= 100)
				{
					on_attack_ex();
					mp = 0;
				}
				break;
			}
		}
		break;
		case WM_KEYUP:
		{
			switch (msg.vkcode)
			{
			case 0x41: // A
				is_left_keydown = false;
				break;
			case 0x44: // D
				is_right_keydown = false;
				break;
			}
		}
		break;
		}
		break;
	case ID::P2:
		switch (msg.message)
		{
		case WM_KEYDOWN:
		{
			switch (msg.vkcode)
			{
			case VK_LEFT: // Left
				is_left_keydown = true;
				break;
			case VK_RIGHT: // Right
				is_right_keydown = true;
				break;
			case VK_UP: // Up
				on_jump();
				break;
			case VK_OEM_PERIOD: // "."
				if (can_attack)
				{
					on_attack();
					timer_attack_cd.restart();
					can_attack = false;
				}
				break;
			case VK_OEM_2: // "/"
				if (mp >= 100)
				{
					on_attack_ex();
					mp = 0;
				}
				break;
			}
		}
		break;
		case WM_KEYUP:
		{
			switch (msg.vkcode)
			{
			case VK_LEFT:// Left
				is_left_keydown = false;
				break;
			case VK_RIGHT: // Right
				is_right_keydown = false;
				break;
			}
		}
		break;
		}
		break;
	}
}

void Player::set_id(ID id)
{
	this->id = id;
}

void Player::set_position(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Player::on_run(float diatance)
{
	if (is_attacking_ex) return;
	position.x += diatance;
	if (position.x < 0) position.x = 0;
	if (position.x > 1280 - 96) position.x = 1280 - 96;
}

void Player::on_jump()
{
	if (velocity.y != 0 || is_attacking_ex) return;
	velocity.y += jump_speed;
}

void Player::on_attack()
{
}

void Player::on_attack_ex()
{
}

void Player::move_and_collide(int delta)
{
	velocity.y += gravity * delta;
	position.y += velocity.y * delta;
	if (velocity.y > 0)
	{
		for (const Platform& platform : platform_list)
		{
			const Platform::CollisionShape shape = platform.shape;
			bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left))
				<= size.x + (shape.right - shape.left);
			bool is_collide_y = position.y <= shape.y&& shape.y <= position.y + size.y;;
			if (is_collide_x && is_collide_y)
			{
				float delta_pos_y = velocity.y * delta;
				float last_tick_pos_y = position.y + size.y - delta_pos_y;
				if (last_tick_pos_y <= shape.y)
				{
					position.y = shape.y - size.y;
					velocity.y = 0;
					break;
				}
			}
		}
	}
	for (Bullet* bullet : bullet_list) 
	{
		if (!bullet->get_valid() || bullet->get_collide_target() != id)
			continue;
		if (bullet->check_collide(position, size))
		{
			bullet->on_collide();
			bullet->set_valid(false);
			if (!is_attacking_ex)
			hp -= bullet->get_damage();
		}
	}
}
void Player::set_hp(int val)
{
	hp = val;
}
const vector2& Player::get_position()
{
	return position;
}

const vector2& Player::get_size()
{
	return size;
}

int Player::get_hp() const
{
	return hp;
}

int Player::get_mp() const
{
	return mp;
}
