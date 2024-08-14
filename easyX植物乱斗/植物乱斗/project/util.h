#pragma once
#include "graphics.h"
#include "camera.h"

inline void fliplr_image(IMAGE* sourse_img, IMAGE* target_img) 
{
	int width = sourse_img->getwidth();
	int height = sourse_img->getheight();
	Resize(target_img, width, height);
	DWORD* source_buffer = GetImageBuffer(sourse_img);
	DWORD* target_buffer = GetImageBuffer(target_img);
    for (int y =0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int idx_source = y * width + x;
			int idx_target = y * width + (width - x - 1);
			target_buffer[idx_target] = source_buffer[idx_source];
		}
	}
}

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int width = img->getwidth();
	int height = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img)
{
	int width = img->getwidth();
	int height = img->getheight();
	const vector2& pos_camera = camera.get_position();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(x - pos_camera.x), (int)(y - pos_camera.y), width, height,
		GetImageHDC(img), 0, 0, width, height, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y)
{
	int w = width > 0 ? width : img->getwidth(); 
	int h = height > 0 ? height : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,	0,255,AC_SRC_ALPHA });
}