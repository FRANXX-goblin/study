#include "pea_bullet.h"
#include "util.h"
extern IMAGE img_pea;
extern Atlas atlas_pea_break; 

pea_bullet::pea_bullet()
{
	size.x = 64;
	size.y = 64;
	damage = 10;

	animation_break.set_atlas(&atlas_pea_break);
	animation_break.set_interval(100);
	animation_break.set_loop(false);
	animation_break.set_callback([&]() {can_remove = true; });
}

pea_bullet::~pea_bullet()
{
}

void pea_bullet::on_collide()
{
	Bullet::on_collide();

	switch (rand() % 3)
	{
	case 0:
		mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
		break;
	case 1:
		mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
		break;
	case 2:
		mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
		break;
	}
}

void pea_bullet::on_update(int delta)
{
	position += velocity * delta;
	if (!valid)
		animation_break.on_update(delta);

	if (check_if_exceeds_screen())
		can_remove = true;
}

void pea_bullet::on_draw(const Camera& camera)
{
	if (valid)
		putimage_alpha(camera, (int)position.x, (int)position.y, &img_pea);
	else
		animation_break.on_draw(camera, (int)position.x, (int)position.y);
}
