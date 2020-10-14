#pragma once

#include "bullet.h"

class ExplosiveBullet : public Bullet
{
    private:
        float   m_range = 5;

    public:
        ExplosiveBullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM);

        bool collision_check(const Enemy&) const override;
        
};