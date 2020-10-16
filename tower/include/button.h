#pragma once

#include <gp/gp.h>

#include "maths.h"
#include "resource_manager.h"

class ButtonManager;

class Button
{
    protected:
        GPLib*      m_gp;
        Vector2     m_lastMousepos;
        Vector2     m_initialPosition;
        bool        m_isPressed = false;
        bool        m_isDragged = false;
        bool        m_isDraggable = false;
        bool        m_isUndragged = false;
        
    public:
        ButtonManager*  m_buttonManager;
        GPTexture       m_texture;
        GPColor         m_color = GP_CWHITE;
        Rectangle       m_rect;

        Button(GPLib* gp, Vector2 position);

        virtual void update();

        virtual void draw(GPLib* gp) const;

        virtual void isPressed();
        virtual void isReleased();
        virtual void isDown(Vector2 mouse_pos);
        virtual void isUp();
        virtual void isHightlighted();
        virtual void isDragged(Vector2 mouse_pos);
        virtual void isUndragged();

        Vector2 getPosition() const;
};