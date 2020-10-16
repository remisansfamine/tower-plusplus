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
                isPressed(mouse_pos);  
            else
                isDown(mouse_pos);
        }
        else isHightlighted();

        if (gpMouseButtonIsReleased(m_gp, GP_MOUSE_BUTTON_1))
            isReleased();
    }
    else isUp();
    
    if (m_isDragged)
        isDragged(mouse_pos);

    m_lastMousepos = mouse_pos;
}

void Button::isPressed(Vector2 mouse_pos)
{
    m_isPressed = true;
}
void Button::isReleased()
{
    m_buttonManager->m_current = nullptr;
    m_isPressed = false;
    
    if (m_isDragged)
        isUndragged();
}
void Button::isDown(Vector2 mousePos)
{
    if (m_lastMousepos != mousePos && m_isPressed)
        m_isDragged = m_isDraggable;
}
void Button::isUp()
{

}
void Button::isHightlighted()
{

}
void Button::isDragged(Vector2 mouse_pos)
{
    m_rect.position = mouse_pos;
}
void Button::isUndragged()
{
    m_isDragged = false;
}

void    Button::draw(GPLib* gp) const
{
    gpDrawTexture(gp, m_texture, m_rect.position, true, m_color);
}
