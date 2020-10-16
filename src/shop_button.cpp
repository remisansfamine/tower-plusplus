#include "shop_button.h"
#include "collisions.h"
#include "game.h"
#include "entity_manager.h"

#include "slowing_tower.h"
#include "explosive_tower.h"
#include "standard_tower.h"

ShopButton::ShopButton(GPLib* gp, Vector2 position,
                       const ResourceManager& RM, TowerType type,
                       EntityManager* EM)
: Button(gp, position), m_entityManager(EM)
{
    m_font = RM.getFont();
    
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

    buyTower();

    Button::update();
}

void ShopButton::draw(GPLib* gp) const
{
    Button::draw(gp);

    std::string price_string = "$" + std::to_string(m_price);

    // Display the index of the last wave
    gpDrawTextAligned(gp, m_font, {m_rect.position.x, m_rect.position.y + TILE_SIZE / 2},
                      {1, 0.7f, 0.27f, 1}, GP_TEXTALIGN_CENTER, price_string.c_str());
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

void ShopButton::buyTower()
{
    if (this == m_buttonManager->m_current)
    {
        for (TowerSlot& slot : Tower::m_towerSlots)
        {  
            if (slot.m_isAvailable &&
            c_point_box(m_rect.position, slot.getCollision()))
            {
                if (m_isUndragged)
                {
                    Game::m_money -= m_price;
                    slot.m_isAvailable = false;
                    switch (m_type)
                    {
                        case TowerType::STANDARD:
                            m_entityManager->createTower(new StandardTower(&slot, m_entityManager->m_resourceManager));
                            break;

                        case TowerType::SLOWING:
                            m_entityManager->createTower(new SlowingTower(&slot, m_entityManager->m_resourceManager));
                            break;

                        case TowerType::EXPLOSIVE:
                            m_entityManager->createTower(new ExplosiveTower(&slot, m_entityManager->m_resourceManager));
                            break;
                    }
                }
            }
        }
    }
}