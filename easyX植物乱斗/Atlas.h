#pragma once
#include <vector>
#include <graphics.h>
using namespace std;

class Atlas
{
public:
	Atlas();
	~Atlas();
	void load_from_file(LPCTSTR path, int num);
	void clear();
	int get_size();
	IMAGE* get_image(int idx);
	void add_image(IMAGE img);

private:
	vector<IMAGE>img_list;
};