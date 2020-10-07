#pragma once

#include "enemy.h"

class WeakEnemy : public Enemy
{
    public:
        WeakEnemy(Vector2 position, const RessourceManager& RM) : Enemy(position)
        {
            m_life = Life(25);
            m_damage = 10;
            m_speed = 25;
            m_texture = RM.get_texture((unsigned int)TextureType::ENEMY_IDLE);
            m_direction = Vector2(5, 3, true);
        }

        void update() override
        {
            move();
        }
};