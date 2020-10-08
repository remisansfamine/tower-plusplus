#pragma once

#include "enemy.h"
#include <iostream>

class StrongEnemy : public Enemy
{
    public:
        StrongEnemy(Vector2 position, const RessourceManager& RM) : Enemy(position)
        {
            m_life = Life(50);
            m_damage = 25;
            m_speed = 100;
            m_texture = RM.get_texture((unsigned int)TextureType::ENEMY_IDLE);
        }

        void update() override
        {
            move();
        }
};