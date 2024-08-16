#include "Enemy.h"
Enemy::Enemy()
{
	direct_x = -1;
	direct_y = 0;
	enum class SpawnEndge
	{
		Up = 0,
		Down,
		Left,
		Right
	};
	SpawnEndge endge = SpawnEndge(rand() % 4);
	switch(endge)
	{
	case SpawnEndge::Up:
		pos.x = rand()%1280;
		pos.y = -80;
		break;
	case SpawnEndge::Down:
		pos.x = rand() % 1280;
		pos.y = 720;
		break;
	case SpawnEndge::Left:
		pos.x = -80;
		pos.y = rand() % 720;
		break;
	case SpawnEndge::Right:
		pos.x = 1280;
		pos.y = rand() % 720;
		break;
	default:
		break;
	}
	shadow_pos.x = pos.x + 23;
	shadow_pos.y = pos.y + 50;
}
Enemy::~Enemy()
{
}

void Enemy::Move(const Player& player)
{
	if (player.pos.x - pos.x <= 10 && player.pos.x - pos.x >= 0) direct_x = 0;
	else if (player.pos.x - pos.x > 0) direct_x = 1;
	else direct_x = -1;
	if (player.pos.y - pos.y <= 10 && player.pos.y - pos.y >= 0) direct_y = 0;
	else if (player.pos.y - pos.y > 0) direct_y = 1;
	else direct_y = -1;

	double normalized = (direct_x != 0 || direct_y != 0) ?
		sqrt(direct_x * direct_x + direct_y * direct_y) / (abs(direct_x) + abs(direct_y)) : 0;
	pos.x += (int)ENEMY_SPEED * direct_x * normalized;
	pos.y += (int)ENEMY_SPEED * direct_y * normalized;
	shadow_pos.x = pos.x + 23;
	shadow_pos.y = pos.y + 50;
}

void Enemy::Draw(Atlas atlas)
{
	Animation::putimage_alpha(shadow_pos.x, shadow_pos.y, &atlas.img_shadow_enemy);

	static bool facing_left = true;
	if (direct_x == 1) facing_left = false;
	else if (direct_x == -1) facing_left = true;

	if (facing_left) atlas.animation_left_enemy->Play(pos.x, pos.y, 0.5*1000 / 60);
    else atlas.animation_right_enemy->Play(pos.x, pos.y, 0.5*1000 / 60);
}

bool Enemy::CheckBulletCollision(Bullet& bullet) const
{
	if ((bullet.pos1.x >= pos.x && bullet.pos1.x <= pos.x + 80 && bullet.pos1.y >= pos.y && bullet.pos1.y <= pos.y + 80)
		|| (bullet.pos2.x >= pos.x && bullet.pos2.x <= pos.x + 80 && bullet.pos2.y >= pos.y && bullet.pos2.y <= pos.y + 80)
		|| (bullet.pos3.x >= pos.x && bullet.pos3.x <= pos.x + 80 && bullet.pos3.y >= pos.y && bullet.pos3.y <= pos.y + 80)
		|| (bullet.pos4.x >= pos.x && bullet.pos4.x <= pos.x + 80 && bullet.pos4.y >= pos.y && bullet.pos4.y <= pos.y + 80))
		return true;
	else
		return false;
}

bool Enemy::CheckPlayerCollision(Player& player) const
{
	if (player.pos.x + 40 >= pos.x && player.pos.x + 40 <= pos.x + 80 && player.pos.y + 40 >= pos.y && player.pos.y + 40 <= pos.y + 80)
		return true;
	else
		return false;
}
