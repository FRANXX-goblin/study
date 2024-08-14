#pragma once	

#include <graphics.h>
#include <iostream>

#include "Atlas.h"
#include "Animation.h"
#include "Camera.h"

#include "util.h"

using namespace std;

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
	virtual void on_enter() {}//进入
	virtual void on_update(int delta) {}//上传
	virtual void on_draw(const Camera camera) {}//绘制
	virtual void on_input(const ExMessage& msg) {}//捕捉玩家输入并执行操作
	virtual void on_exit() {}//退出
	static void fliplr_atlas(Atlas& source, Atlas& target)
	{
		target.clear();
		for (int i = 0; i < source.get_size(); i++)
		{
			IMAGE img_flipped;
			fliplr_image(source.get_image(i), &img_flipped);
			target.add_image(img_flipped);
		}
	}

private:
};