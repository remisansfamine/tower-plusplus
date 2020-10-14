#pragma once

#include <string>

#include <gp/gp.h>

#include "maths.h"
#include "life.h"

class Renderer;
class EntityManager;

class Entity
{
    protected:
        std::string name;

        float   m_damage;
        
        Vector2     m_position;
        Vector2     m_direction;
        GPTexture   m_texture;
        Renderer*   m_renderer = nullptr;
    public:
        EntityManager* m_EntityManager;

        bool    m_should_destroy = false;

        Life    m_life;

        Entity(Vector2 position);

        GPTexture get_texture() const;

        float get_damage() const;
        float X() const;
        float Y() const;
        Vector2 get_position() const;

        virtual void update(float delta_time) = 0;
};