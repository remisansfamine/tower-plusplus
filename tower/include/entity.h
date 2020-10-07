#pragma once

#include <string>

#include <gp/gp.h>

#include "game.h"
#include "maths.h"
#include "render_manager.h"
#include "life.h"

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
        Life    m_life;

        Entity(Vector2 position) : m_position(position) {}

        GPTexture get_texture() const { return m_texture; }

        float X() const { return m_position.x; }
        float Y() const { return m_position.y; }
        Vector2 get_position() const { return m_position; }

        virtual void update() = 0;
};