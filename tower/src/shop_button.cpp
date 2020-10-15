#include "shop_button.h"

#include "game.h"

ShopButton::ShopButton(GPLib* gp, Vector2 position, const ResourceManager& RM, TowerType type)
: Button(gp, position)
{
    m_initial_position = position;

    m_type = type;

    switch (type)
    {
        case TowerType::STANDARD:
            m_texture = RM.get_texture(TextureType::STANDARD_IDLE);
            m_price = 5;
            break;

        case TowerType::SLOWING:
            m_texture = RM.get_texture(TextureType::SLOWING_IDLE);
            m_price = 7;
            break;

        case TowerType::EXPLOSIVE:
            m_texture = RM.get_texture(TextureType::EXPLOSIVE_IDLE);
            m_price = 10;
            break;
    }
}

void ShopButton::update()
{
    m_is_draggable = Game::m_money >= m_price;
    m_color.a = m_is_draggable ? 1 : 0.5f;
    Button::update();
}

void ShopButton::is_pressed(Vector2 mouse_pos)
{
    Button::is_pressed(mouse_pos);
    m_ButtonManager->m_current = this;
}

void ShopButton::is_undragged()
{
    Button::is_undragged();
    m_rect.position = m_initial_position;
    m_ButtonManager->m_current = nullptr;
}

int ShopButton::get_price() const
{
    return m_price;
}

TowerType ShopButton::get_type() const
{
    return m_type;
}
