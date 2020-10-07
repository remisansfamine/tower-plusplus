#pragma once

#include "enemy.h"

class HealerEnemy : public Enemy
{
    public:
        HealerEnemy(Vector2 position, const RessourceManager& RM) : Enemy(position)
        {
            m_life = Life(25);
            m_damage = 5;
            m_speed = 40;
            m_texture = RM.get_texture((unsigned int)TextureType::ENEMY_IDLE);
        }
    
        void update() override
        {
            move();
        }
};