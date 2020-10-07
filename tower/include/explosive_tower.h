#pragma once

#include "tower.h"

class ExplosiveTower : public Tower
{
    public:
        ExplosiveTower(Vector2 position, const RessourceManager& RM) : Tower(position)
        {
            m_life = Life(15);
            m_damage = 10.f;
            m_fire_rate = 5;
            m_range = 60;
            m_texture = RM.get_texture((unsigned int)TextureType::TOWER_IDLE);
        }

        void update() override
        {
        }
};