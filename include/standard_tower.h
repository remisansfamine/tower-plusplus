#pragma once

#include "tower.h"

class StandardTower : public Tower
{
    public:
        StandardTower(Vector2 position, const RessourceManager& RM) : Tower(position)
        {
            m_life = Life(25);
            m_damage = 5;
            m_fire_rate = 10;
            m_range = 75;
            m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
        }

        void update() override
        {
        }
};