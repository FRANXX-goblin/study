#include "GameScene.h"
#include "SceneManager.h"
#include "Platform.h"
#include "Player.h"
#include "Bullet.h"

extern SceneManager scene_manager;
extern Camera main_camera;
extern vector<Platform>platform_list;
extern Player* player_1;
extern Player* player_2;
extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;
extern vector<Bullet*> bullet_list;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

GameScene::GameScene()
{
}
GameScene::~GameScene() = default;

void GameScene::on_enter()
{
	status_bar_1P.set_avatar(img_player_1_avatar);
	status_bar_2P.set_avatar(img_player_2_avatar);

	status_bar_1P.set_position(235, 625);
	status_bar_2P.set_position(675, 625);

	pos_img_sky.x = (1280 - img_sky.getwidth()) / 2;
	pos_img_sky.y = (720 - img_sky.getheight()) / 2;

	pos_img_hills.x = (1280 - img_hills.getwidth()) / 2;
	pos_img_hills.y = (720 - img_hills.getheight()) / 2;

	platform_list.resize(4);

	Platform& large_platform = platform_list[0]; 
	large_platform.img = &img_platform_large; 
	large_platform.render_position.x = 122; 
	large_platform.render_position.y = 455;
	large_platform.shape.left = (float)large_platform.render_position.x + 30;
	large_platform.shape.right = (float)large_platform.render_position.x + img_platform_large.getwidth() - 30;
	large_platform.shape.y = (float)large_platform.render_position.y + 60;

	Platform& small_platform_1 = platform_list[1]; small_platform_1.img = &img_platform_small; 
	small_platform_1.render_position.x = 175; small_platform_1.render_position.y = 360;
	small_platform_1.shape.left = (float)small_platform_1.render_position.x + 40;
	small_platform_1.shape.right = (float)small_platform_1.render_position.x + img_platform_small.getwidth() - 40;
	small_platform_1.shape.y = (float)small_platform_1.render_position.y + img_platform_small.getheight() / 2;

	Platform& small_platform_2 = platform_list[2]; small_platform_2.img = &img_platform_small; small_platform_2.render_position.x = 855; small_platform_2.render_position.y = 360;
	small_platform_2.shape.left = (float)small_platform_2.render_position.x + 40;
	small_platform_2.shape.right = (float)small_platform_2.render_position.x + img_platform_small.getwidth() - 40; 
	small_platform_2.shape.y = (float)small_platform_2.render_position.y + img_platform_small.getheight() / 2;

	Platform& small_platform_3 = platform_list[3]; small_platform_3.img = &img_platform_small; small_platform_3.render_position.x = 515; small_platform_3.render_position.y = 225;
	small_platform_3.shape.left = (float)small_platform_3.render_position.x + 40;
	small_platform_3.shape.right = (float)small_platform_3.render_position.x + img_platform_small.getwidth() - 40; 
	small_platform_3.shape.y = (float)small_platform_3.render_position.y + img_platform_small.getheight() / 2;

	player_1->on_start();
	player_2->on_start();

	mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
}

void GameScene::on_update(int delta)
{
	const vector2 player_1_position = player_1->get_position();
	const vector2 player_2_position = player_2->get_position();
	if (player_1_position.y > 720)player_1->set_hp(0);
	if (player_2_position.y > 720)player_2->set_hp(0);

	if (player_1->get_hp() == 0||player_2->get_hp() == 0)
	{
		MessageBox(GetHWnd(), player_1->get_hp() == 0 ? _T("Winner: Player 2") : _T("Winner: Player 1"), _T("Game Over"), MB_OK);
		mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
		scene_manager.switch_to(SceneManager::SceneType::Menu);
	}

	player_1->on_update(delta);
	player_2->on_update(delta);

	main_camera.on_update(delta);

	for (Bullet* bullet : bullet_list)
		bullet->on_update(delta);

	bullet_list.erase(std::remove_if(
		bullet_list.begin(), bullet_list.end(), [](const Bullet* bullet) {
			bool deletable = bullet->check_can_remove(); 
			if (deletable) delete bullet; 
			return deletable; }),
			bullet_list.end());

	status_bar_1P.set_hp(player_1->get_hp());
	status_bar_1P.set_mp(player_1->get_mp()); 
	status_bar_2P.set_hp(player_2->get_hp()); 
	status_bar_2P.set_mp(player_2->get_mp());

}

void GameScene::on_draw(const Camera camera)
{	
	putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
	putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

	for (Platform& platform : platform_list)
	{
		platform.on_draw(camera);
	}

	player_1->on_draw(camera);
	player_2->on_draw(camera);

	for (Bullet* bullet : bullet_list)
	{
		bullet->on_draw(camera);
	}

	status_bar_1P.on_draw();
	status_bar_2P.on_draw();
}

void GameScene::on_input(const ExMessage& msg)
{
	player_1->on_input(msg);
	player_2->on_input(msg);
}

void GameScene::on_exit()
{
}