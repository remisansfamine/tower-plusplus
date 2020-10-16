#include <cmath>

#include "define.h"

#include "maths.h"
#include "collisions.h"
#include "game.h"

#include "slowing_tower.h"
#include "explosive_tower.h"
#include "standard_tower.h"

#include "shop_button.h"

#include <gp/gp.h>

int Game::m_money = 10;

Game::Game(GPLib* gp)
: m_gp(gp), m_resourceManager(gp),
m_entityManager(m_resourceManager, gp),
m_map(m_resourceManager), m_hud(&m_entityManager)
{
    for (int i = 0; i < (int)TowerType::COUNT; i++)
    {
        Vector2 position = {SCREEN_WIDTH - TILE_SIZE * (2 + i * 3) / 2, TILE_SIZE};
        m_buttonManager.createButton(new ShopButton(gp, position,
                                                    m_resourceManager, (TowerType)i));
    }
}

void Game::update()
{
    Vector2 mousePos = gpMousePosition(m_gp);

    float deltaTime = getDeltaTime();

    m_buttonManager.update();

    for (TowerSlot& slot : Tower::m_towerSlots)
    {  
        if (!m_buttonManager.m_current)
            break;

        if (slot.m_isAvailable && c_point_box(mousePos, slot.getCollision()))
        {
            if (m_buttonManager.m_current->m_isUndragged)
            {
                m_money -= m_buttonManager.m_current->getPrice();
                slot.m_isAvailable = false;
                switch (m_buttonManager.m_current->getType())
                {
                    case TowerType::STANDARD:
                        m_entityManager.createTower(new StandardTower(&slot, m_resourceManager));
                        break;

                    case TowerType::SLOWING:
                        m_entityManager.createTower(new SlowingTower(&slot, m_resourceManager));
                        break;

                    case TowerType::EXPLOSIVE:
                        m_entityManager.createTower(new ExplosiveTower(&slot, m_resourceManager));
                        break;
                }
            }
        }
    }

    
    m_entityManager.update(deltaTime);
}

void Game::display() const
{   
    m_map.draw(m_gp);
    
    m_entityManager.draw();

    m_hud.draw(m_gp);

    m_buttonManager.draw(m_gp);
}

float Game::getDeltaTime()
{
    if (gpKeyIsPressed(m_gp, GP_KEY_P))
        m_isPaused = !m_isPaused;

    if (gpKeyIsPressed(m_gp, GP_KEY_LEFT) && m_gameSpeed > 0)
        m_gameSpeed -= 0.5f;

    if (gpKeyIsPressed(m_gp, GP_KEY_RIGHT))
        m_gameSpeed += 0.5f;

    return gpGetFrameTime(m_gp) * (m_isPaused ? 0 : m_gameSpeed);
}