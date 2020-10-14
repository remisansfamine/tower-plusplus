#pragma once

#include "bullet.h"

class SlowingBullet : public Bullet
{
    public:
        SlowingBullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM);

        void hit(Enemy&) override;
};