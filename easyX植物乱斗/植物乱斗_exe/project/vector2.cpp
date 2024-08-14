#include "vector2.h"
#include <corecrt_math.h>

vector2::vector2()
{
}

vector2::vector2(float x, float y):x(x), y(y)
{
}

vector2::~vector2()
{
}

vector2 vector2::operator+(const vector2& other) const
{
	return vector2(x + other.x, y + other.y);
}

vector2 vector2::operator-(const vector2& other) const
{
	return vector2(x - other.x, y - other.y);
}

vector2 vector2::operator*(float scalar) const
{
	return vector2(x * scalar, y * scalar);
}

vector2 vector2::operator/(float scalar) const
{
	return vector2(x / scalar, y / scalar);
}

void vector2::operator+=(const vector2& other)
{
	x += other.x;
	y += other.y;
}

void vector2::operator-=(const vector2& other)
{
	x -= other.x;
	y -= other.y;
}

void vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
}

float vector2::operator*(const vector2& other) const
{
	return x * other.x + y * other.y;
}

float vector2::length() const
{
	return sqrt(x * x + y * y);
}

vector2 vector2::normalize() const
{
	float length = this->length();

	if (length == 0) { return vector2(0, 0); }

	return vector2(x / length, y / length);
}



