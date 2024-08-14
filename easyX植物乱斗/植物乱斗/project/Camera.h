#pragma once
#include "vector2.h"
#include "Timer.h"
class Camera
{
public:
    Camera();
    ~Camera();
    const vector2& get_position() const;
    void reset();
    void on_update(int delta);

public:
    void shake(float strength, int duration);

private:
    vector2 position;
    const vector2 camera_speed = { -0.35f, 0 };

private:
    bool is_shaking = false;
    Timer shake_timer;
    float shake_strength = 0;
};

