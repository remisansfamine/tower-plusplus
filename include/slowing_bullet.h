#pragma once

#include "bullet.h"

class SlowingBullet : public Bullet
{
    public:
        SlowingBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM);

        void hit(Enemy&) override;
};