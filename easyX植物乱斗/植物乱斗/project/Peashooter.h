#pragma once
#include "Player.h"
#include "pea_bullet.h"
class Peashooter :
    public Player
{
public:
    Peashooter();
    ~Peashooter();

public:
    void on_update(int delta);
    void on_attack();
    void on_attack_ex();

private:
    void spawn_pea_bullet(float speed);
    const float speed_pea = 0.75f;
    const float speed_pea_ex = 1.5f;
    const int attack_ex_duration = 2500;
private:
    Timer  timer_attack_ex;
    Timer  timer_spawn_pea_ex;
};

