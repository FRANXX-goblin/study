#include "util.h"
#include "Atlas.h"

#include "SceneManager.h"
#include "Platform.h"

#include "Bullet.h"
#include "Player.h"

#pragma comment(lib, "winmm.lib")

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

IMAGE img_menu_background;

IMAGE img_VS;
IMAGE img_1P;
IMAGE img_2P;
IMAGE img_1P_desc;
IMAGE img_2P_desc;
IMAGE img_gravestone_left;
IMAGE img_gravestone_right;
IMAGE img_selector_tip;
IMAGE img_selector_background;
IMAGE img_1P_selector_btn_idle_left;
IMAGE img_1P_selector_btn_idle_right;
IMAGE img_1P_selector_btn_down_left;
IMAGE img_1P_selector_btn_down_right;
IMAGE img_2P_selector_btn_idle_left;
IMAGE img_2P_selector_btn_idle_right;;
IMAGE img_2P_selector_btn_down_left;
IMAGE img_2P_selector_btn_down_right;
IMAGE img_peashooter_selector_background_left;
IMAGE img_peashooter_selector_background_right;
IMAGE img_sunflower_selector_background_left;
IMAGE img_sunflower_selector_background_right;


IMAGE img_sky;
IMAGE img_hills;
IMAGE img_platform_large;
IMAGE img_platform_small;

IMAGE img_1P_cursor;
IMAGE img_2P_cursor;

Atlas atlas_peashooter_idle_left;
Atlas atlas_peashooter_idle_right;
Atlas atlas_peashooter_run_left;
Atlas atlas_peashooter_run_right;
Atlas atlas_peashooter_attack_ex_left;
Atlas atlas_peashooter_attack_ex_right;
Atlas atlas_peashooter_die_left;
Atlas atlas_peashooter_die_right;

Atlas atlas_sunflower_idle_left;
Atlas atlas_sunflower_idle_right;
Atlas atlas_sunflower_run_left;
Atlas atlas_sunflower_run_right;
Atlas atlas_sunflower_attack_ex_left;
Atlas atlas_sunflower_attack_ex_right;
Atlas atlas_sunflower_die_left;
Atlas atlas_sunflower_die_right;

IMAGE img_pea; 
Atlas atlas_pea_break;
Atlas atlas_sun;
Atlas atlas_sun_explode;
Atlas atlas_sun_ex;
Atlas atlas_sun_ex_explode;
Atlas atlas_sun_text;

Atlas atlas_run_effect;
Atlas atlas_jump_effect;
Atlas atlas_land_effect;

IMAGE img_1P_winner;
IMAGE img_2P_winner;
IMAGE img_winner_bar;

IMAGE img_avatar_peashooter;
IMAGE img_avatar_sunflower;

SceneManager scene_manager;

Player* player_1;
Player* player_2;

IMAGE* img_player_1_avatar = nullptr;
IMAGE* img_player_2_avatar = nullptr;

Camera main_camera;

vector<Bullet*>bullet_list;

vector<Platform>platform_list;

int main()
{
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

    loadimage(&img_menu_background, _T("resources/menu_background.png"));
    
    loadimage(&img_sky, _T("resources/sky.png"));
    loadimage(&img_hills, _T("resources/hills.png"));
    loadimage(&img_platform_large, _T("resources/platform_large.png"));
    loadimage(&img_platform_small, _T("resources/platform_small.png"));
    

    loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
    loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));
    atlas_peashooter_idle_right.load_from_file(_T("resources/peashooter_idle_%d.png"), 9);
    fliplr_atlas(atlas_peashooter_idle_right, atlas_peashooter_idle_left);
    atlas_peashooter_run_right.load_from_file(_T("resources/peashooter_run_%d.png"), 5);
    fliplr_atlas(atlas_peashooter_run_right, atlas_peashooter_run_left);
    atlas_peashooter_attack_ex_right.load_from_file(_T("resources/peashooter_attack_ex_%d.png"), 3);
    fliplr_atlas(atlas_peashooter_attack_ex_right, atlas_peashooter_attack_ex_left);
    atlas_peashooter_die_right.load_from_file(_T("resources/peashooter_die_%d.png"), 4);
    fliplr_atlas(atlas_peashooter_die_right, atlas_peashooter_die_left);
    atlas_sunflower_idle_right.load_from_file(_T("resources/sunflower_idle_%d.png"), 8);
    fliplr_atlas(atlas_sunflower_idle_right, atlas_sunflower_idle_left);
    atlas_sunflower_run_right.load_from_file(_T("resources/sunflower_run_%d.png"), 5);
    fliplr_atlas(atlas_sunflower_run_right, atlas_sunflower_run_left);
    atlas_sunflower_attack_ex_right.load_from_file(_T("resources/sunflower_attack_ex_%d.png"), 9);
    fliplr_atlas(atlas_sunflower_attack_ex_right, atlas_sunflower_attack_ex_left);
    atlas_sunflower_die_right.load_from_file(_T("resources/sunflower_die_%d.png"), 2);
    fliplr_atlas(atlas_sunflower_die_right, atlas_sunflower_die_left);


    loadimage(&img_pea, _T("resources/pea.png"));
    atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
    atlas_sun.load_from_file(_T("resources/sun_%d.png"), 5);
    atlas_sun_explode.load_from_file(_T("resources/sun_explode_%d.png"), 5);
    atlas_sun_ex.load_from_file(_T("resources/sun_ex_%d.png"), 5);
    atlas_sun_ex_explode.load_from_file(_T("resources/sun_ex_explode_%d.png"), 5);
    atlas_sun_text.load_from_file(_T("resources/sun_text_%d.png"), 6);


    atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
    atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
    atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);
    loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
    loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
    loadimage(&img_winner_bar, _T("resources/winnner_bar.png"));
    loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));
    mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
    mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);

    constexpr int FPS = 60;
    constexpr int delta = 1000 / FPS;

    bool runnig = true;

    ExMessage msg;



    initgraph(1280, 720, EW_SHOWCONSOLE);

    settextstyle(28, 0, _T("IPix"));
    setbkmode(TRANSPARENT);

    BeginBatchDraw();

    mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
    while (runnig)
    {
        DWORD start_time = GetTickCount();

        while (peekmessage(&msg))
        {
            scene_manager.on_input(msg);
        }

        static DWORD last_time = GetTickCount();
        DWORD current_time = GetTickCount();
        scene_manager.on_update(current_time - last_time);
        last_time = current_time;

        cleardevice();

        scene_manager.on_draw(main_camera);

        FlushBatchDraw();
        DWORD end_time = GetTickCount();
        if (end_time - start_time < delta)
        {
            Sleep(1000 / FPS - (end_time - start_time));
        }
    }
    EndBatchDraw();

    closegraph();

    return 0;
}