#include <cmath>

#include <iostream>
#include <algorithm>

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
m_map(m_resourceManager)
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

    for (TowerSlot& slot : Tower::m_towerSlots)
    {  
        if (!m_buttonManager.m_current || !slot.m_isAvailable)
            continue;

        if (c_point_box(mousePos, slot.getCollision()))
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
            m_buttonManager.m_current->isUndragged();
        }
    }

    m_buttonManager.update();
    
    m_entityManager.update(deltaTime);
}

void Game::display() const
{   
    m_map.draw(m_gp);
    
    m_entityManager.draw();

    m_hud.draw(m_gp);

    m_buttonManager.draw(m_gp);

    std::string wave_string = "Wave " + std::to_string(m_entityManager.getWaveIndex()) +
                              "/" + std::to_string(m_entityManager.getWaveCount()) + " - ";
    
    int timer = m_entityManager.getTimer();

    if (timer > 0)
        wave_string += "Next wave in: " + std::to_string(timer) + "s";
    else
    {
        int enemy_count = m_entityManager.getEnemyCount();
        wave_string += std::to_string(enemy_count) +
                      (enemy_count > 1 ? " enemies" : " enemy") + " left";
    }

    gpDrawTextAligned(m_gp, m_resourceManager.getFont(), {SCREEN_WIDTH / 2, 25},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, wave_string.c_str());

    std::string money_string = "Money: $" + std::to_string(m_money);
    gpDrawTextAligned(m_gp, m_resourceManager.getFont(), {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, money_string.c_str());
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