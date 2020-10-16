#include "button.h"

#include "button_manager.h"
#include "define.h"
#include "collisions.h"

Button::Button(GPLib* gp, Vector2 position)
: m_gp(gp)
{
    m_rect = {position, TILE_SIZE / 2, TILE_SIZE / 2};
}

void    Button::update()
{
    if (m_isUndragged)
        isUndragged();

    Vector2 mousePos = gpMousePosition(m_gp);

    if (c_point_box(mousePos, m_rect))
    {
        if (gpMouseButtonIsDown(m_gp, GP_MOUSE_BUTTON_1))
        {
            if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_1))
                isPressed();  
            else
                isDown(mousePos);
        }
        else isHightlighted();

        if (gpMouseButtonIsReleased(m_gp, GP_MOUSE_BUTTON_1))
            isReleased();
    }
    else isUp();
    
    if (m_isDragged)
        isDragged(mousePos);

    m_lastMousepos = mousePos;
}

void    Button::isPressed()
{
    m_isPressed = true;
}

void    Button::isReleased()
{
    m_isPressed = false;
    
    if (m_isDraggable)
        m_isUndragged = true;
}

void    Button::isDown(Vector2 mousePos)
{
    if (m_lastMousepos != mousePos && m_isPressed)
        m_isDragged = m_isDraggable;
}

void    Button::isUp()
{

}

void    Button::isHightlighted()
{

}

void    Button::isDragged(Vector2 mousePos)
{
    m_rect.position = mousePos;
}

void    Button::isUndragged()
{
    m_buttonManager->m_current = nullptr;

    m_isUndragged = false;
    m_isDragged = false;
}

void    Button::draw(GPLib* gp) const
{
    gpDrawTexture(gp, m_texture, m_rect.position, true, m_color);
}

Vector2 Button::getPosition() const
{
    return m_rect.position;
}