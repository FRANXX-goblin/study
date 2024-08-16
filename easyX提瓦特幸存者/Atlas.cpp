#include "Atlas.h"

Atlas::Atlas()
{
	loadimage(&img_shadow_player, "./res/img/shadow_player.png");
	loadimage(&img_shadow_enemy, "./res/img/shadow_enemy.png");
	animation_left_player = new Animation(_T("./res/img/player_left_%d.png"), 6, 1000 / 60 * 7);
	animation_right_player = new Animation(_T("./res/img/player_right_%d.png"), 6, 1000 / 60 * 7);
	animation_left_enemy = new Animation(_T("./res/img/enemy_left_%d.png"), 6, 1000 / 60 * 7);
	animation_right_enemy = new Animation(_T("./res/img/enemy_right_%d.png"), 6, 1000 / 60 * 7);
}
Atlas::~Atlas()
{
}
