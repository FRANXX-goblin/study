#pragma once
#include "Camera.h"
#include "util.h"
class Platform
{
public:
	Platform();
	~Platform();

public:
	struct CollisionShape
	{
		float y;
		float left, right;
	};

public:
	CollisionShape shape;
	IMAGE* img = nullptr;
	POINT render_position = { 0 };

public:
	void on_draw(const Camera& camera);
};

