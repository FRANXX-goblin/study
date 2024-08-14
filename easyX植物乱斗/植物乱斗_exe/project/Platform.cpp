#include "Platform.h"

Platform::Platform()
{
}

Platform::~Platform()
{
}

void Platform::on_draw(const Camera& camera)
{
	putimage_alpha(camera, render_position.x, render_position.y, img);
}
