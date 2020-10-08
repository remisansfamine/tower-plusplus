#pragma once

#include "tower_slot.h"
#include "game.h"
#include "entity.h"

#include "ressource_manager.h"

class Tower : public Entity
{
    public:
        static std::vector<TowerSlot> tower_slots;

        float   m_fire_rate;
        float   m_cooldown;
        float   m_range;

        Tower(Vector2 position) : Entity(position) { }
};