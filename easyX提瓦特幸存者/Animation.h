#pragma once
#include<graphics.h>
#include <vector>
#include <string>
#pragma comment(lib,"MSIMG32.LIB")
using namespace std;
class Animation
{
public:
	Animation();
	Animation(LPCTSTR path, int num, int interval);
	~Animation();
	void Play(int x, int y, int delta);
	static void putimage_alpha(int x, int y, IMAGE* img);
private:
	int interval_ms = 0;
	int idx_frame = 0;
	int timer = 0;
	vector<IMAGE*>frame_list;
};

