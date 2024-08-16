#include "Animation.h"
#include <tchar.h>

Animation::Animation() {};
Animation::Animation(LPCTSTR path,int num,int interval)
{
	interval_ms = interval;
	TCHAR path_file[256];
	for (int i = 0; i < num; i++) 
	{
		_stprintf_s(path_file, path, i);
		IMAGE* frame = new IMAGE;
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

Animation::~Animation() 
{
    
}

void Animation::putimage_alpha(int x, int y, IMAGE* img)
{
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void Animation::Play(int x,int y,int delta) 
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idx_frame = (idx_frame + 1) % frame_list.size();
		timer = 0;
	}
	putimage_alpha(x, y, frame_list[idx_frame]);
}
