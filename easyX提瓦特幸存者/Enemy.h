#pragma once
#include "Atlas.h"
#include "Player.h"
#include "Bullet.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move(const Player& player) ;
	void Draw(Atlas atlas);
	bool CheckBulletCollision(Bullet& bullet) const;
	bool CheckPlayerCollision(Player& player) const;
private:
	POINT pos;
	POINT shadow_pos;
	IMAGE img_shadow;
	const int ENEMY_SPEED = 3;
	int direct_x;
	int direct_y;
};

