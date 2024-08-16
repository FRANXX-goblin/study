#pragma once
#include "Animation.h"
class Atlas
{
public:
	Atlas();
	~Atlas();
	Animation* animation_left_player;
	Animation* animation_right_player;
	Animation* animation_left_enemy;
	Animation* animation_right_enemy;
	IMAGE img_shadow_player;
	IMAGE img_shadow_enemy;
};

