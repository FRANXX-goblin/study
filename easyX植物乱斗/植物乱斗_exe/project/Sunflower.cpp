﻿#include "Sunflower.h"
#include <iostream>

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;

extern Player* player_1;
extern Player* player_2;
extern vector<Bullet*> bullet_list;
Sunflower::Sunflower()
{
	animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
	animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
	animation_run_left.set_atlas(&atlas_sunflower_run_left);
	animation_run_right.set_atlas(&atlas_sunflower_run_right);
	animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
	animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
	animation_sun_text.set_atlas(&atlas_sun_text);

	animation_idle_left.set_interval(75);
	animation_idle_right.set_interval(75);
	animation_run_left.set_interval(75);
	animation_run_right.set_interval(75);
	animation_attack_ex_left.set_interval(100);
	animation_attack_ex_right.set_interval(100);
	animation_sun_text.set_interval(100);

	size.x = 96;
	size.y = 96;

	animation_attack_ex_left.set_loop(false);
	animation_attack_ex_right.set_loop(false);
	animation_sun_text.set_loop(false);

	animation_attack_ex_left.set_callback([&]()
		{
			is_attacking_ex = false;
			is_sun_text_visible = false;
		});
	animation_attack_ex_right.set_callback([&]()
		{
			is_attacking_ex = false;
			is_sun_text_visible = false;
		});

	attack_cd = 250;
}

Sunflower::~Sunflower()
{
}

void Sunflower::on_update(int delta)
{
	Player::on_update(delta);
	if (is_attacking_ex)
	{ 
		animation_sun_text.on_update(delta);
	}
}

void Sunflower::on_draw(const Camera& camera)
{
	Player::on_draw(camera);

	if (is_attacking_ex)
	{
		vector2 text_position;
		IMAGE*frame=animation_sun_text.get_frame();
		text_position.x = position.x - (size.x - frame->getwidth()) / 2;
		text_position.y = position.y - frame->getheight();
		animation_sun_text.on_draw(camera, (int)text_position.x, (int)text_position.y);
	}
}

void Sunflower::on_attack()
{
	Bullet* bullet = new sun_bullet();

	vector2 bullet_position;
	const vector2& bullet_size = bullet->get_size();
	bullet_position.x = position.x + (size.x - bullet_size.x) / 2;
	bullet_position.y = position.y;

	bullet->set_position(bullet_position.x, bullet_position.y);
	bullet->set_velocity(is_facing_right ? velocity_sun.x : -velocity_sun.x, velocity_sun.y);

	bullet->set_collide_target(id == ID::P1 ? ID::P2 : ID::P1);

	bullet->set_callback([&]() {mp += 35; });

	bullet_list.push_back(bullet);
}

void Sunflower::on_attack_ex()
{
	is_attacking_ex = true;
	is_sun_text_visible = true;
	animation_sun_text.reset();
	is_facing_right? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

	Bullet* bullet = new sun_bullet_ex();
	Player* target_player = id == ID::P1 ? player_2 : player_1;

	vector2 bullet_position, bullet_velocity;
	const vector2& bullet_size = bullet->get_size();
	const vector2& target_size = target_player->get_size();
	const vector2& target_position = target_player->get_position();
	bullet_position.x = target_position.x + (target_size.x - bullet_size.x) / 2;
	bullet_position.y = -bullet_size.y;
	bullet_velocity.x = 0;
	bullet_velocity.y = speed_sun_ex;

	bullet->set_position(bullet_position.x, bullet_position.y);
	bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);
	bullet->set_collide_target(id == ID::P1 ? ID::P2 : ID::P1);
	bullet->set_callback([&]() { mp += 50; }); 
	bullet_list.push_back(bullet);
	mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);
}



