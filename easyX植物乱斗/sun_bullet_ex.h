#pragma once
#include "Bullet.h"
class sun_bullet_ex :
    public Bullet
{
public:
    sun_bullet_ex();
    ~sun_bullet_ex();
    void on_collide();
    void on_update(int delta);
    void on_draw(const Camera& camera);
    bool check_collide(const vector2& position, const vector2& size);
private:
    Animation animation_idle;
    Animation animation_explode;
    vector2 explode_render_offset;
};

