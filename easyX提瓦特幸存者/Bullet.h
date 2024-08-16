#pragma once
#include<graphics.h>
#include<math.h>
#include "Player.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define RADIUS 10
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Draw();
	void Move(const Player& player) ;
	POINT pos1, pos2, pos3, pos4;
private:
	double angle1, angle2, angle3, angle4;
	const double speed;
	const int a13, b13, a24, b24;
};

