#pragma once
#include "Bullet.h"
class sun_bullet :
    public Bullet
{
public:
    sun_bullet();
    ~sun_bullet();

public:
    void on_collide();
    void on_update(int delta);
    void on_draw(const Camera& camera);

private:
    const float gravity = 1e-3f;
    Animation animation_idle;
    Animation animation_explode;
    vector2 explode_render_offset;
};

