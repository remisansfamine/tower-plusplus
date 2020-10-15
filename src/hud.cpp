#include "hud.h"

void    HUD::draw(GPLib* gp) const
{
    gpDrawRectFilled(gp, {912.f, 16.f, 272.f, 88.f}, {0, 0, 0, 0.5f});
}