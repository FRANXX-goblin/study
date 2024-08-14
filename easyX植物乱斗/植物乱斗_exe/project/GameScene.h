#pragma once
#include "Scene.h"
#include "util.h"
#include "status_bar.h"

class GameScene :
    public Scene
{
public:
    GameScene();
    ~GameScene();

public:
    void on_enter();
    void on_update(int delta);
    void on_draw(const Camera camera);
    void on_input(const ExMessage& msg);
    void on_exit();

private:
    POINT pos_img_sky = { 0 };
    POINT pos_img_hills = { 0 };

private:
    status_bar status_bar_1P;
    status_bar status_bar_2P;
};

