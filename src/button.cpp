#include "map.h"

#include "button.h"

#include "collisions.h"

#include "button_manager.h"

#include <iostream>

Button::Button(GPLib* gp, Vector2 position)
: m_gp(gp)
{
    m_rect = {position, TILE_SIZE / 2, TILE_SIZE / 2};
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
    m_ButtonManager->m_current = nullptr;
    m_is_pressed = false;
    
    if (m_is_dragged)
        is_undragged();
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
void Button::is_undragged()
{
    m_is_dragged = false;
}

void    Button::draw(GPLib* gp) const
{
    gpDrawRectFilled(gp, GPRect{m_initial_position.x - TILE_SIZE / 3 * 2, m_initial_position.y - TILE_SIZE / 3 * 2, TILE_SIZE * 3 / 2, TILE_SIZE * 3 / 2}, GPColor{0, 0, 0, 0.5f});
}
