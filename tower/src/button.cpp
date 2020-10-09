#include "button.h"

#include "collisions.h"

#include <iostream>

Button::Button(GPLib* gp, Vector2 position, const ResourceManager& RM)
: m_gp(gp)
{
    m_rect = {position, 50.f, 50.f};
    m_texture = RM.get_texture(TextureType::BUTTON);
}

void Button::update()
{
    Vector2 mousePos = gpMousePosition(m_gp);
    if (c_point_box(mousePos, m_rect) &&
        gpMouseButtonIsDown(m_gp, GP_MOUSE_BUTTON_1))
        std::cout << "oui" << std::endl;
}

bool Button::isPressed() { return true; }
bool Button::isReleased() { return true; }
bool Button::isDown() { return true; }
bool Button::isUp() { return true; }