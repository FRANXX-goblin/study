#include "SceneManager.h"


SceneManager::SceneManager() 
{
	menu_scene = new MenuScene; 
	selector_scene = new SelectorScene;
	game_scene = new GameScene;
	set_current_scene(menu_scene);
}
SceneManager::~SceneManager()
{
	delete menu_scene;
	delete selector_scene;
	delete game_scene;
}


void SceneManager::set_current_scene(Scene* scene)
{
	current_scene = scene;
	current_scene->on_enter();
}

void SceneManager::switch_to(SceneType type)
{
	current_scene->on_exit();
	switch (type)
	{
	case SceneType::Menu:
		current_scene = menu_scene;
		break;
	case SceneType::Selector:
		current_scene = selector_scene;
		break;
	case SceneType::Game:
		current_scene = game_scene;
		break;
	default:
		break;
	}
	current_scene->on_enter();
}


void SceneManager::on_update(int delta) { current_scene->on_update(delta); }
void SceneManager::on_draw(const Camera camera) { current_scene->on_draw(camera); }
void SceneManager::on_input(const ExMessage& msg) { current_scene->on_input(msg); }
