#include "sun_bullet.h"

extern Camera main_camera;

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;

sun_bullet::sun_bullet()
{
	size.x = 96;
	size.y = 96;

	explode_render_offset.x = 48;
	explode_render_offset.y = 48;

	damage = 20;

	animation_idle.set_atlas(&atlas_sun);
	animation_idle.set_interval(50);

	animation_explode.set_atlas(&atlas_sun_explode);
	animation_explode.set_interval(50);
	animation_explode.set_loop(false);
	animation_explode.set_callback([&]() {can_remove = true; });
}

sun_bullet::~sun_bullet()
{
}


void sun_bullet::on_collide()
{
	Bullet::on_collide();

	main_camera.shake(5, 250);

	mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
}

void sun_bullet::on_update(int delta)
{
	if (valid)
	{
		velocity.y += gravity * delta;
		position += velocity * delta;
	}
	if (!valid)
		animation_explode.on_update(delta);
	else
		animation_idle.on_update(delta);

	if (check_if_exceeds_screen())
		can_remove = true;
}

void sun_bullet::on_draw(const Camera& camera)
{
	if (valid)
		animation_idle.on_draw(camera, (int)position.x, (int)position.y);
	else
		animation_explode.on_draw(camera,
			(int)(position.x - explode_render_offset.x),
			(int)(position.y - explode_render_offset.y));
}