#include "Player.h"

Player::Player() 
{
	is_move_up = false;
	is_move_down = false;
	is_move_left = false;
	is_move_right = false;
	pos = { 500,500 };
	shadow_pos = { 523,570 };
}

Player::~Player()
{

}

void Player::Move()
{
	while (peekmessage(&msg))
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = true;
				break;
			case VK_DOWN:
				is_move_down = true;
				break;
			case VK_LEFT:
				is_move_left = true;
				break;
			case VK_RIGHT:
				is_move_right = true;
				break;
			}
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case VK_UP:
				is_move_up = false;
				break;
			case VK_DOWN:
				is_move_down = false;
				break;
			case VK_LEFT:
				is_move_left = false;
				break;
			case VK_RIGHT:
				is_move_right = false;
				break;
			}
		}
	}

	int direct_x = is_move_right - is_move_left;
	int direct_y = is_move_down - is_move_up;
	double normalized = (direct_x != 0 || direct_y != 0) ?
		sqrt(direct_x * direct_x + direct_y * direct_y) / (abs(direct_x) + abs(direct_y)) : 0;

	pos.x += (int)PLAYER_SPEED * direct_x * normalized;
	pos.y += (int)PLAYER_SPEED * direct_y * normalized;
	shadow_pos.x = pos.x + 23;
	shadow_pos.y = pos.y + 70;

	if (pos.x < 0) { pos.x = 0; shadow_pos.x = 23; }
	if (pos.x > 1200) { pos.x = 1200; shadow_pos.x = 1223; }
	if (pos.y < 0) { pos.y = 0; shadow_pos.y = 70; }
	if (pos.y > 640) { pos.y = 640; shadow_pos.y = 710; }
}

void Player::Draw(Atlas atlas)
{
	int direct_x = is_move_right - is_move_left;
	static bool facing_left = true;
	if (direct_x > 0)facing_left = false;
	else if (direct_x < 0)facing_left = true;

	Animation::putimage_alpha(shadow_pos.x, shadow_pos.y, &atlas.img_shadow_player);
	if (facing_left)atlas.animation_left_player->Play(pos.x, pos.y, 1000 / 60);
	else atlas.animation_right_player->Play(pos.x, pos.y, 1000 / 60);
}
	

