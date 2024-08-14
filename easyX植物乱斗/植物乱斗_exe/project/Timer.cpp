#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::restart()
{
	pass_time = 0;
	shotted = false;
}

void Timer::set_wait_time(int val)
{
	wait_time = val;
}

void Timer::set_one_shot(bool flag)
{
	one_shot = flag;
}

void Timer::pause()
{
	paused = true;
}

void Timer::resume()
{
	paused = false;
}

void Timer::on_update(int delta)
{
	if (paused)return;
	pass_time += delta;
	if (pass_time >= wait_time)
	{
		if(!one_shot||(one_shot&&!shotted)&&callback)
			callback();
		shotted = true;
		pass_time = 0;
	}
}

void Timer::set_callback(std::function<void()> callback)
{
	this->callback = callback;
}
