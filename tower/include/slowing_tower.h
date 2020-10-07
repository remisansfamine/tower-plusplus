#pragma once

#include "tower.h"

class SlowingTower : public Tower
{
    public:
        SlowingTower(Vector2 position, const RessourceManager& RM) : Tower(position)
        {
            m_life = Life(40);
            m_damage = 2.5f;
            m_fire_rate = 25;
            m_range = 45;
            m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
        }

        void update() override
        {
        }
};