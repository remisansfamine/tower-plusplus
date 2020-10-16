#include "shop_button.h"

#include "game.h"

ShopButton::ShopButton(GPLib* gp, Vector2 position,
                       const ResourceManager& RM, TowerType type)
: Button(gp, position)
{
    m_initialPosition = position;

    m_type = type;

    switch (type)
    {
        case TowerType::STANDARD:
            m_texture = RM.getTexture(TextureType::STANDARD_IDLE);
            m_price = 5;
            break;

        case TowerType::SLOWING:
            m_texture = RM.getTexture(TextureType::SLOWING_IDLE);
            m_price = 7;
            break;

        case TowerType::EXPLOSIVE:
            m_texture = RM.getTexture(TextureType::EXPLOSIVE_IDLE);
            m_price = 10;
            break;
    }
}

void ShopButton::update()
{
    m_isDraggable = Game::m_money >= m_price;
    m_color.a = m_isDraggable ? 1 : 0.5f;
    Button::update();
}

void ShopButton::isPressed()
{
    Button::isPressed();

    if (m_isDraggable)
        m_buttonManager->m_current = this;
}

void ShopButton::isUndragged()
{
    Button::isUndragged();
    
    m_rect.position = m_initialPosition;
    m_buttonManager->m_current = nullptr;
}

int ShopButton::getPrice() const
{
    return m_price;
}

TowerType ShopButton::getType() const
{
    return m_type;
}
