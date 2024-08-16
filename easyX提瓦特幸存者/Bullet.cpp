#include "Bullet.h"
Bullet::Bullet()
	: angle1(0), angle2(M_PI / 2), angle3(M_PI), angle4(3 * M_PI / 2),
	a13(100), b13(60), a24(60), b24(100), speed(0.1)
{
	setlinecolor(RED);
	setfillcolor(RED);
}

Bullet::~Bullet() 
{
}

void Bullet::Move(const Player& player)
{
	angle1 += speed;
	angle2 += speed;
	angle3 += speed;
	angle4 += speed;
	angle1 = (angle1 > 2 * M_PI) ? angle1 - 2 * M_PI : angle1;
	angle2 = (angle2 > 2 * M_PI) ? angle2 - 2 * M_PI : angle2;
	angle3 = (angle3 > 2 * M_PI) ? angle3 - 2 * M_PI : angle3;
	angle4 = (angle4 > 2 * M_PI) ? angle4 - 2 * M_PI : angle4;

	POINT center;
	center.x = player.pos.x + 40;
	center.y = player.pos.y + 40;

	pos1.x = center.x + a13 * cos(angle1);
	pos1.y = center.y + b13 * sin(angle1);

	pos2.x = center.x + a24 * cos(angle2);
	pos2.y = center.y + b24 * sin(angle2);

	pos3.x = center.x + a13 * cos(angle3);
	pos3.y = center.y + b13 * sin(angle3);

	pos4.x = center.x + a24 * cos(angle4);
	pos4.y = center.y + b24 * sin(angle4);
}

void Bullet::Draw() 
{
	fillcircle(pos1.x, pos1.y, RADIUS);
	fillcircle(pos2.x, pos2.y, RADIUS);
	fillcircle(pos3.x, pos3.y, RADIUS);
	fillcircle(pos4.x, pos4.y, RADIUS);
}


