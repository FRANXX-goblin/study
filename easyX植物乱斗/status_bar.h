#pragma once
#include "util.h"
class status_bar
{
public:
    status_bar();
    ~status_bar();
public:
    void set_avatar(IMAGE* avatar);
    void set_position(int x, int y);
    void set_hp(int val);
    void set_mp(int val);
    void on_draw();
private:
    int hp = 0;
    int mp = 0;
    IMAGE* img_avatar = nullptr;
    POINT position = { 0,0 };
    const int width = 275;
};

