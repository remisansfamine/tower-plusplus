#pragma once

#include <string>

#include <gp/gp.h>

#include "maths.h"
#include "life.h"

class EntityManager;

class Entity
{
    protected:
        std::string name;

        float   m_damage;
        
        Vector2     m_position;
        Vector2     m_direction;
        GPTexture   m_texture;
    public:
        EntityManager* m_EntityManager;

        bool    m_should_destroy = false;

        Life    m_life;

        Entity(Vector2 position);

        float X() const;
        float Y() const;
        Vector2 get_position() const;

        virtual void update(float delta_time) = 0;

        virtual void draw(GPLib* gp) = 0;
};