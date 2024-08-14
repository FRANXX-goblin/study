#pragma once
#include "Bullet.h"

class pea_bullet :
    public Bullet
{
public:
    pea_bullet();
    ~pea_bullet();
public:
    void on_collide();
    void on_update(int delta);
    void on_draw(const Camera& camera);

private:
    Animation animation_break;
};

