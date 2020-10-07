#pragma once

#include "game.h"
#include "entity.h"

#include "ressource_manager.h"

class Tower : public Entity
{
    public:
        float   m_fire_rate;
        float   m_cooldown;
        float   m_range;

        Tower(Vector2 position) : Entity(position) { }
};