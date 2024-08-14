#pragma once
#include<graphics.h>
#include<functional>
#pragma comment(lib,"MSIMG32.LIB")

#include "Atlas.h"
#include "Camera.h"
#include "util.h"

using namespace std;

class Animation
{
public:
	Animation();
	~Animation();
	void reset();
	void set_atlas(Atlas* new_atlas);
	void set_loop(bool flag);
	void set_interval(int ms);
	int get_idx_frame() const;
	IMAGE* get_frame();
	bool check_finished();
	void on_update(int delta);
	void on_draw(const Camera& camera, int x, int y);
	void set_callback(function<void()>callback);
private:
	int interval = 0;
	int idx_frame = 0;
	int timer = 0;
	bool is_loop = true;
	Atlas* atlas = nullptr;
	function<void()>callback;
};