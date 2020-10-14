#pragma once

#include "bullet.h"

class StandardBullet : public Bullet
{
    public:
        StandardBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM);
};