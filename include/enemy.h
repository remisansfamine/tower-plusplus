#pragma once

#include "entity.h"

#include "ressource_manager.h"

class Enemy : public Entity
{
    protected:
        float   m_speed;
        
    public:
        Enemy(float x, float y, float life, float speed, const RessourceManager& RM) : Entity(x, y, life), m_speed(speed)
        {

        }

        //void update() override;
};