#pragma once

#include "tower_slot.h"
#include "entity.h"

#include <vector>

#include "resource_manager.h"

class Tower : public Entity
{
    public:
        static std::vector<TowerSlot> tower_slots;

        float   m_fire_rate;
        float   m_cooldown;
        float   m_range;

        Tower(Vector2 position);
};