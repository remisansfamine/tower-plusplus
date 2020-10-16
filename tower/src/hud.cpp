#include "hud.h"
#include "define.h"

#include "game.h"

#include <string>

HUD::HUD(EntityManager* EM) : m_entityManager(EM)
{
    m_font = m_entityManager->m_resourceManager.getFont();
}

void    HUD::draw(GPLib* gp) const
{
    gpDrawRectFilled(gp, {912.f, TILE_SIZE / 4, 272.f, TILE_SIZE * 3 / 2},
                    {0, 0, 0, 0.5f});

    if (m_entityManager->m_gameState == GameState::RUNNING)
    {
        displayWavesState(gp);
        drawCastleLife(gp);
    }
    else if (m_entityManager->m_gameState == GameState::WIN)
    {
        gpDrawTextAligned(gp, m_font, {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, "***YOU WIN***");
    }
    else drawGameOver(gp);
}

void    HUD::displayWavesState(GPLib* gp) const
{
    std::string wave_string = "Wave " + std::to_string(m_entityManager->getWaveIndex()) +
                              "/" + std::to_string(m_entityManager->getWaveCount()) + " - ";
    
    int timer = m_entityManager->getTimer();

    // If the wave is not over, display the number of enemies 
    if (timer <= 0)
    {
        int enemy_count = m_entityManager->getEnemyCount();
        wave_string += std::to_string(enemy_count) +
                      (enemy_count > 1 ? " enemies" : " enemy") + " left";
    }
    // Else display the remaining time until the next wave
    else
        wave_string += "Next wave in: " + std::to_string(timer) + "s";

    gpDrawTextAligned(gp, m_font, {SCREEN_WIDTH / 2, 25},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, wave_string.c_str());

    std::string money_string = "Money: $" + std::to_string(Game::m_money);

    // Display the money
    gpDrawTextAligned(gp, m_font, {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, money_string.c_str());
}

void    HUD::drawCastleLife(GPLib* gp) const
{
    float life = m_entityManager->m_castle.m_life;
    float maxLife = m_entityManager->m_castle.m_maxLife;

    GPRect lifebar = {SCREEN_WIDTH / 2 - TILE_SIZE, 2 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE / 4};
    gpDrawRectFilled(gp, lifebar, {1, 0, 0, 1});

    lifebar.w *= life / maxLife;
    gpDrawRectFilled(gp, lifebar, {0, 1, 0, 1});

    lifebar.w /= life / maxLife;
    gpDrawRect(gp, lifebar, GP_CBLACK);
}

void    HUD::drawGameOver(GPLib* gp) const
{
    gpDrawTextAligned(gp, m_font, {SCREEN_WIDTH / 2, 25},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, "-- GAME OVER ! --");

    std::string wave_string = "Number of waves survived: " + std::to_string(m_entityManager->getWaveIndex());

    // Display the index of the last wave
    gpDrawTextAligned(gp, m_font, {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, wave_string.c_str());
}
