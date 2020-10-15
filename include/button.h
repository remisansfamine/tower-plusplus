#pragma once

#include <gp/gp.h>

#include "maths.h"
#include "resource_manager.h"

class ButtonManager;
class Button
{
    protected:
        GPLib*      m_gp;
        bool        m_is_pressed = false;
        bool        m_is_dragged = false;
        bool        m_is_draggable = false;
        Vector2     m_last_mousepos;
        Vector2     m_initial_position;

    public:
        ButtonManager*   m_ButtonManager;
        GPTexture   m_texture;
        GPColor     m_color = GP_CWHITE;
        Rectangle   m_rect;

        Button(GPLib* gp, Vector2 position);

        virtual void update();

        virtual void is_pressed(Vector2 mouse_pos);
        virtual void is_released();
        virtual void is_down(Vector2 mouse_pos);
        virtual void is_up();
        virtual void is_hightlighted();
        virtual void is_dragged(Vector2 mouse_pos);
        virtual void is_undragged();

        virtual void    draw(GPLib* gp) const;
};