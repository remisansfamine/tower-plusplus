#pragma once

#include "game.h"
#include "entity.h"

#include "ressource_manager.h"

class Tower : public Entity
{
    protected:
        float   m_fire_rate;
        float   m_range;
        //int     m_cost;

    public:
        Tower(Vector2 position) : Entity(position) { }
};