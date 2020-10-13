#include "button.h"

#include "collisions.h"

#include <iostream>

Button::Button(GPLib* gp, Vector2 position)
: m_gp(gp)
{
    m_rect = {position, 50.f, 50.f};
}

void Button::update()
{
    Vector2 mouse_pos = gpMousePosition(m_gp);

    if (c_point_box(mouse_pos, m_rect))
    {
        if (gpMouseButtonIsDown(m_gp, GP_MOUSE_BUTTON_1))
        {
            if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_1))
                is_pressed(mouse_pos);  
            else
                is_down(mouse_pos);
        }
        else is_hightlighted();

        if (gpMouseButtonIsReleased(m_gp, GP_MOUSE_BUTTON_1))
            is_released();
    }
    else is_up();
    
    if (m_is_dragged)
        is_dragged(mouse_pos);

    m_last_mousepos = mouse_pos;
}

void Button::is_pressed(Vector2 mouse_pos)
{
    m_is_pressed = true;
}
void Button::is_released()
{
    m_is_pressed = false;
    m_is_dragged = false;
}
void Button::is_down(Vector2 mouse_pos)
{
    if (m_last_mousepos != mouse_pos && m_is_pressed)
        m_is_dragged = m_is_draggable;
}
void Button::is_up()
{

}
void Button::is_hightlighted()
{

}

void Button::is_dragged(Vector2 mouse_pos)
{
    m_rect.position = mouse_pos;
}