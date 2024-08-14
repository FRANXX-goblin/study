#pragma once
#include "Scene.h"

class SelectorScene :
	public Scene
{
public:
	SelectorScene();
	~SelectorScene();

public:
	void on_enter();
	void on_update(int delta);
	void on_draw(const Camera camera);
	void on_input(const ExMessage& msg);
	void on_exit();

private:
	enum class PlayerType
	{
		Peashooter = 0,
		Sunflower,
		Invalid
	};

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str);

private:
	int selector_background_scroll_offset_x = 0;

	bool is_btn_1P_left_down = false;
	bool is_btn_1P_right_down = false;
	bool is_btn_2P_left_down = false;
	bool is_btn_2P_right_down = false;

	PlayerType player_1P_type = PlayerType::Peashooter;
	PlayerType player_2P_type = PlayerType::Sunflower;

	Animation animation_peashooter;
	Animation animation_sunflower;

	LPCTSTR str_peashooter_name = _T("婉逗射手");
	LPCTSTR str_sunflower_name = _T("龙日葵");

	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };
};
