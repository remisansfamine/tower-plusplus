#pragma once

#include "tower.h"

class ExplosiveTower : public Tower
{
    public:
        ExplosiveTower(Vector2 position, const RessourceManager& RM) : Tower(position)
        {
            m_life = Life(15);
            m_damage = 10;
            m_cooldown = m_fire_rate = 2.5f;
            m_range = 250;
            m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
        }

        void update() override
        {
            m_cooldown -= delta_time;   
        }
};