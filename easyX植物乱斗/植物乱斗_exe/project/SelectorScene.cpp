#include "SelectorScene.h"
#include "SceneManager.h"
#include "Peashooter.h"
#include "Sunflower.h"
extern SceneManager scene_manager;
extern Player* player_1;
extern Player* player_2;
extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;
extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

extern IMAGE img_VS;
extern IMAGE img_1P;
extern IMAGE img_2P;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;
extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;
extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;
extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;
extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;
extern IMAGE img_peashooter_selector_background_left;
extern IMAGE img_peashooter_selector_background_right;
extern IMAGE img_sunflower_selector_background_left;
extern IMAGE img_sunflower_selector_background_right;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_right;
extern IMAGE img_avatar_peashooter;
extern IMAGE img_avatar_sunflower;

SelectorScene::SelectorScene()
{
	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	fliplr_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	fliplr_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	fliplr_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	fliplr_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	fliplr_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
	fliplr_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
	loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
	fliplr_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);
	
	animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
	animation_sunflower.set_atlas(&atlas_sunflower_idle_right); 
	animation_peashooter.set_interval(100); 
	animation_sunflower.set_interval(100); 

	static const int OFFSET_X = 50;

	pos_img_VS.x = (1280 - img_VS.getwidth()) / 2;
	pos_img_VS.y = (720 - img_VS.getheight()) / 2;
	pos_img_tip.x = (1280 - img_selector_tip.getwidth()) / 2;
	pos_img_tip.y = 720 - 125;
	pos_img_1P.x = (1280 / 2 - img_1P.getwidth()) / 2 - OFFSET_X; 
	pos_img_1P.y = 35;
	pos_img_2P.x = 1280 / 2 + (1280 / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
	pos_img_2P.y = pos_img_1P.y;
	pos_img_1P_desc.x = (1280 / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X; 
	pos_img_1P_desc.y = 720 - 150;
	pos_img_2P_desc.x = 1280 / 2 + (1280 / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X; 
	pos_img_2P_desc.y = pos_img_1P_desc.y;
	pos_img_1P_gravestone.x = (1280 / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X; 
	pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
	pos_img_2P_gravestone.x = 1280 / 2 + (1280 / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
	pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
	pos_animation_1P.x = (1280 / 2 - 96) / 2 - OFFSET_X; 
	pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
	pos_animation_2P.x = 1280 / 2 + (1280 / 2 - 96) / 2 + OFFSET_X; 
	pos_animation_2P.y = pos_animation_1P.y;
	pos_img_1P_name.y = pos_animation_1P.y + 155;
	pos_img_2P_name.y = pos_img_1P_name.y;
	pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
	pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight() / 2;
	pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
	pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
	pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
	pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
	pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
	pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;
	
}
SelectorScene::~SelectorScene() = default;

void SelectorScene::on_enter()
{
}

void SelectorScene::on_update(int delta)
{
	animation_peashooter.on_update(delta);
	animation_sunflower.on_update(delta);
	selector_background_scroll_offset_x += 5;
	if (selector_background_scroll_offset_x >= img_peashooter_selector_background_left.getwidth())
		selector_background_scroll_offset_x = 0;

}

void SelectorScene::on_draw(const Camera camera)
{
	IMAGE* img_p1_selector_background = nullptr;
	IMAGE* img_p2_selector_background = nullptr;	
	switch (player_1P_type)
	{
	case PlayerType::Peashooter:
		img_p1_selector_background = &img_sunflower_selector_background_right;
		break;
	case PlayerType::Sunflower:
		img_p1_selector_background = &img_peashooter_selector_background_right;
		break;
	default:
		img_p1_selector_background = &img_peashooter_selector_background_right; 
		break;
	};

	switch (player_2P_type)
	{
	case PlayerType::Peashooter:
		img_p2_selector_background = &img_sunflower_selector_background_left;
		break;
	case PlayerType::Sunflower:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	default:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	};

	putimage(0, 0, &img_selector_background);

	putimage_alpha(selector_background_scroll_offset_x - img_p1_selector_background->getwidth(), 0, img_p1_selector_background);
	putimage_alpha(selector_background_scroll_offset_x, 0,
		(img_p1_selector_background->getwidth() - selector_background_scroll_offset_x), 0, img_p1_selector_background, 0, 0);
	putimage_alpha(getwidth() - img_p2_selector_background->getwidth(), 0, 
		(img_p2_selector_background->getwidth() - selector_background_scroll_offset_x), 0, img_p2_selector_background, selector_background_scroll_offset_x, 0);
	putimage_alpha(getwidth() - selector_background_scroll_offset_x, 0, img_p2_selector_background);

	putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);
	putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P); 
	putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
	putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
	putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left); 
	switch (player_1P_type)
	{
	case PlayerType::Peashooter:
		animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
		break;
	}
	switch (player_2P_type)
	{
	case PlayerType::Peashooter:
		animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
		break;
	}
	putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
	putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);
	putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);

	putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y,
		is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
	putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y,
		is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
	putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y,
		is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
	putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y,
		is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);
	putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
	putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

	putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
}

void SelectorScene::on_input(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (msg.vkcode)
		{
			//'A'
		case 0x41:
			is_btn_1P_left_down = true;
			break;
			// 'D' 
		case 0x44:
			is_btn_1P_right_down = true;
			break;
		case VK_LEFT:
			is_btn_2P_left_down = true;
			break;
		case VK_RIGHT:
			is_btn_2P_right_down = true;
			break;
		case VK_RETURN:	
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager.switch_to(SceneManager::SceneType::Game);
			break;
		default:
			break;
		}
		break;

	case WM_KEYUP:
		switch (msg.vkcode)		
		{
		case 0x41:
			is_btn_1P_left_down = false;
			player_1P_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_1P_type - 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
			//'D
		case 0x44:
			is_btn_1P_right_down = false;
			player_1P_type = (PlayerType)(((int)player_1P_type + 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case VK_LEFT:
			is_btn_2P_left_down = false;
			player_2P_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_2P_type - 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		case VK_RIGHT:
			is_btn_2P_right_down = false;
			player_2P_type = (PlayerType)(((int)player_2P_type + 1) % (int)PlayerType::Invalid);
			mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
		break; 

	defalut:
		break;
	}
}

void SelectorScene::on_exit()
{
	switch (player_1P_type)
	{
	case PlayerType::Peashooter:
		player_1= new Peashooter();
		img_player_1_avatar = &img_avatar_peashooter;
		break;
	case PlayerType::Sunflower:
		player_1 = new Sunflower();
		img_player_1_avatar = &img_avatar_sunflower;
		break;	
	}
	player_1->set_id(ID::P1);
	switch (player_2P_type)
	{
	case PlayerType::Peashooter:
		player_2 = new Peashooter();
		img_player_2_avatar = &img_avatar_peashooter;
		break;
	case PlayerType::Sunflower:
		player_2 = new Sunflower();
		img_player_2_avatar = &img_avatar_sunflower; 
		break;
	}
	player_2->set_id(ID::P2);
	mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
}

void SelectorScene::outtextxy_shaded(int x, int y, LPCTSTR str)
{
	settextcolor(RGB(45, 45, 45));
	outtextxy(x + 3, y + 3, str);
	settextcolor(RGB(255, 255, 255));
	outtextxy(x, y, str);
}
