#include "button.h"

#include "collisions.h"

#include <iostream>

Button::Button(GPLib* gp, Vector2 position, const ResourceManager& RM)
: m_gp(gp)
{
    m_rect = {position, 50.f, 50.f};
    m_texture = RM.get_texture(TextureType::TOWER_IDLE);
}

void Button::update()
{
    Vector2 mousePos = gpMousePosition(m_gp);
    if (c_point_box(mousePos, m_rect) &&
        gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_1))
        {
            std::cout << "oui" << std::endl;
        m_is_pressed = true;
        }
    else m_is_pressed = false;
}

bool Button::isPressed() { return m_is_pressed; }
bool Button::isReleased() { return m_is_released; }
bool Button::isDown() { return m_is_down; }
bool Button::isUp() { return m_is_up; }