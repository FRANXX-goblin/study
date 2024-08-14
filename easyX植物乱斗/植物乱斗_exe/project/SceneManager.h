#pragma once
#include <graphics.h>

#include "MenuScene.h"
#include "SelectorScene.h"
#include "GameScene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();


public:
	enum class SceneType
	{
		Menu,
		Selector,
		Game
	};


public:
	void set_current_scene(Scene* scene);
	void switch_to(SceneType type);
	void on_update(int delta);
	void on_draw(const Camera camera);
	void on_input(const ExMessage& msg);


private:
	Scene* current_scene = nullptr;
	MenuScene* menu_scene = nullptr;
	SelectorScene* selector_scene = nullptr;
	GameScene* game_scene = nullptr;
};
