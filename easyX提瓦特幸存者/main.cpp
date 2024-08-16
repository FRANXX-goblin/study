#include <graphics.h>
#include "Atlas.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#pragma comment(lib,"Winmm.lib")

vector<Enemy*>enemy_list;
static void SpawnEnemy(int interval)
{   
	static int counter = 0;
	if(++counter>interval)
	{	
		enemy_list.push_back(new Enemy());
		counter = counter % interval;
	}

}

int main() 
{
	initgraph(1280, 720);
	
	IMAGE img_background;
	loadimage(&img_background, "./res/img/background.png", 1280, 720);

	mciSendString(_T("open ./res/mus/bgm.mp3 alias bgm"), NULL, 0, NULL);

	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

	mciSendString(_T("open ./res/mus/hit.wav alias hit"), NULL, 0, NULL);

    bool running = true;

	Atlas atlas;

	Player player;

	Bullet bullet;

	BeginBatchDraw();
	while (running) {
		DWORD start_time = GetTickCount();

		cleardevice();
		putimage(0, 0, &img_background);

		player.Move();
		player.Draw(atlas);

		bullet.Move(player);
		bullet.Draw();

		SpawnEnemy(15);
		for(Enemy* enemy:enemy_list)
		{
			enemy->Move(player);
			enemy->Draw(atlas);
		}
		for (int i = enemy_list.size() - 1; i >= 0; --i)
		{
			if (enemy_list[i]->CheckBulletCollision(bullet))
			{
				mciSendString(_T("play hit from 0"), NULL, 0, NULL);
				delete enemy_list[i];
				enemy_list.erase(enemy_list.begin() + i);
			}
		}
		for (int i = 0; i < enemy_list.size(); i++)
		{
			Enemy* enemy;
			enemy = enemy_list[i];
			if(enemy->CheckPlayerCollision(player))
			{
				MessageBox(GetHWnd(), "点击看派蒙战败CG","游戏结束",MB_OK);
				running = false;
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time <= 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	delete atlas.animation_left_player;
	delete atlas.animation_right_player;
	delete atlas.animation_left_enemy;
	delete atlas.animation_right_enemy;
}