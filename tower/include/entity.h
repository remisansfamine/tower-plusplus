#pragma once

#include <string>

#include <gp/gp.h>

#include "maths.h"

class EntityManager;

class Entity
{
    protected:
        float   m_angle;
        float   m_damage;
        
        Vector2     m_position;
        Vector2     m_direction;
        GPTexture   m_texture;

        void    setAngle(Vector2 target);

    public:
        EntityManager* m_entityManager;

        bool    m_shouldDestroy = false;

        float   m_life;
        float   m_max_life;

        Entity(Vector2 position);

        float X() const;
        float Y() const;
        Vector2 getPosition() const;

        virtual void update(float delta_time) {};

        virtual void draw(GPLib* gp) = 0;
};