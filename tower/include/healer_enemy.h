#pragma once

#include "enemy.h"

class HealerEnemy : public Enemy
{
    private:
        float   m_range = 50;
        float   m_healRate = 1.5f;
        Enemy*  m_target = nullptr;

    public:
        HealerEnemy(Vector2 position, const ResourceManager& RM);
    
        void update(float delta_time) override;

        void draw(GPLib* gp) override;
};