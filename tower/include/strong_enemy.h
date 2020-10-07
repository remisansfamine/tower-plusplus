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
            m_waypoints[0] = Vector2(0, 0);
            m_waypoints[1] = Vector2(6, 5);
            m_waypoints[2] = Vector2(100, 250);
            m_waypoints[3] = Vector2(750, 0);
            m_waypoints[4] = Vector2(0, 3);
            m_waypoints[5] = Vector2(500, 800);
        }

        void update() override
        {
            move();
        }
};