#include <cmath>

#include "define.h"

#include "maths.h"
#include "collisions.h"
#include "game.h"

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
                                                    m_resourceManager, (TowerType)i, &m_entityManager));
    }
}

void    Game::update()
{
    if (m_entityManager.m_gameState != GameState::RUNNING)
        return;
        
    float deltaTime = getDeltaTime();

    m_buttonManager.update();
    
    m_entityManager.update(deltaTime);
}

void    Game::display() const
{   
    m_map.draw(m_gp);
    
    m_entityManager.draw();

    m_hud.draw(m_gp);

    m_buttonManager.draw(m_gp);
}

float   Game::getDeltaTime()
{
    if (gpKeyIsPressed(m_gp, GP_KEY_P) || gpKeyIsPressed(m_gp, GP_KEY_ESCAPE))
        m_isPaused = !m_isPaused;

    if (gpKeyIsPressed(m_gp, GP_KEY_LEFT) && m_gameSpeed > 0)
        m_gameSpeed -= 0.5f;

    if (gpKeyIsPressed(m_gp, GP_KEY_RIGHT))
        m_gameSpeed += 0.5f;

    return gpGetFrameTime(m_gp) * (m_isPaused ? 0 : m_gameSpeed);
}