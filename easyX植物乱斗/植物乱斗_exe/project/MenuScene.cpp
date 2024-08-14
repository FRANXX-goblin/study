#pragma comment(lib, "winmm.lib")
#include "MenuScene.h"
#include "SceneManager.h"
extern SceneManager scene_manager;

extern IMAGE img_menu_background;

MenuScene::MenuScene() { }
MenuScene::~MenuScene() = default;

void MenuScene::on_enter()
{
	mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
}

void MenuScene::on_update(int delta)
{

}

void MenuScene::on_draw(const Camera camera)
{
	putimage(0, 0, &img_menu_background);
}

void MenuScene::on_input(const ExMessage& msg)
{
	if (msg.message==WM_KEYDOWN)
	{
		mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
		scene_manager.switch_to(SceneManager::SceneType::Selector);
	}
}

void MenuScene::on_exit()
{
}