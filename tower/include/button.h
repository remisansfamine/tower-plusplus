#pragma once

#include <gp/gp.h>

#include "maths.h"
#include "resource_manager.h"

class Button
{
    private:
        GPLib*      m_gp;
        bool        m_is_pressed = false;
        bool        m_is_released = false;
        bool        m_is_down = false;
        bool        m_is_up = true;

    public:
        GPTexture   m_texture;
        Rectangle   m_rect;

        Button(GPLib* gp, Vector2 position, const ResourceManager& RM);

        void update();

        virtual bool isPressed();
        virtual bool isReleased();
        virtual bool isDown();
        virtual bool isUp();
};