#pragma once
#include "Player.h"
#include "sun_bullet.h"
#include "sun_bullet_ex.h"
class Sunflower :
    public Player
{
public:
    Sunflower();
    ~Sunflower();
public:
    void on_update(int delta);
    void on_draw(const Camera& camera);
    void on_attack();
    void on_attack_ex();

private:
    const float speed_sun_ex = 0.3f;
    const vector2 velocity_sun = { 0.25f,-0.5f };

private:
    Animation animation_sun_text;
    bool is_sun_text_visible = false;
};

