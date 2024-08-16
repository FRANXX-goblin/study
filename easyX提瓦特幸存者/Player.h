#pragma once
#include "Atlas.h"
class Player
{
public:
    Player();
    ~Player();
    POINT pos;
    void Move();
    void Draw(Atlas atlas);
private:
    ExMessage msg;
    IMAGE img_shadow;
    const int PLAYER_SPEED = 10;
    POINT shadow_pos;
    bool is_move_up;
    bool is_move_down;
    bool is_move_left;
    bool is_move_right;
};

 