#include "Camera.h"

Camera::Camera()
{
	shake_timer.set_one_shot(true);
	shake_timer.set_callback([&]() {
		is_shaking = false;
		reset(); });
}

Camera::~Camera()
{
}

const vector2& Camera::get_position() const
{
	return position;
}

void Camera::reset()
{
	position.x = 0;
	position.y = 0;
}

void Camera::on_update(int delta)
{
	shake_timer.on_update(delta);
	if (is_shaking)
	{
		position.x = (-50 + rand() % 101) / 50.0f * shake_strength;
		position.y = (-50 + rand() % 101) / 50.0f * shake_strength;
	}
}

void Camera::shake(float strength, int duration)
{
	is_shaking = true;
	shake_strength = strength;

	shake_timer.set_wait_time(duration);
	shake_timer.restart();
}
