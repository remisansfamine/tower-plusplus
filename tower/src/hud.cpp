#include "hud.h"
#include "define.h"

#include "game.h"

#include <string>

HUD::HUD(EntityManager* EM) : m_entityManager(EM)
{

}


void    HUD::draw(GPLib* gp) const
{
    gpDrawRectFilled(gp, {912.f, TILE_SIZE / 4, 272.f, TILE_SIZE * 11 / 8}, {0, 0, 0, 0.5f});

    displayWavesState(gp);
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

    gpDrawTextAligned(gp, m_entityManager->m_resourceManager.getFont(), {SCREEN_WIDTH / 2, 25},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, wave_string.c_str());

    // Display the money
    std::string money_string = "Money: $" + std::to_string(Game::m_money);
    gpDrawTextAligned(gp, m_entityManager->m_resourceManager.getFont(), {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, money_string.c_str());
}