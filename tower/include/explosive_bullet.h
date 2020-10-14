#pragma once

#include "bullet.h"

class ExplosiveBullet : public Bullet
{
    private:
        float   m_range = 100;

    public:
        ExplosiveBullet(Vector2 position, Enemy* enemy, const ResourceManager& RM);

        void hit(Enemy&) override;

        void draw(GPLib* gp) override;  
};