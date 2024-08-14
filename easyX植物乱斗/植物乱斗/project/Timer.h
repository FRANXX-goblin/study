#pragma once
#include <functional>
class Timer
{
public:
	Timer();
	~Timer();

public:
	void restart();
	void set_wait_time(int val);
	void set_one_shot(bool flag);
	void pause();
	void resume();
	void on_update(int delta);
	void set_callback(std::function<void()> callback);
private:
	int pass_time = 0;
	int wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> callback;
};

