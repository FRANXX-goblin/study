#pragma once
#include "Scene.h"


class MenuScene :
    public Scene
{
public:
    MenuScene();
    ~MenuScene();

public:
	void on_enter();
	void on_update(int delta);
	void on_draw(const Camera camera);
	void on_input(const ExMessage& msg);
	void on_exit();
private:
    
};

