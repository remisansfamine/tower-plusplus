#pragma once

#include "enemy.h"

class HealerEnemy : public Enemy
{
    private:
        float   m_range = 50;
        float   m_healRate = 1.5f;
        Enemy*  m_target = nullptr;

        void    getTarget();

        void    healTarget(float deltaTime);

        Circle  getCircle() const;

    public:
        HealerEnemy(Vector2 position, const ResourceManager& RM);
    
        void    update(float deltaTime) override;

        void    draw(GPLib* gp) override;
};