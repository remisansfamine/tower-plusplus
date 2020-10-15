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
: m_gp(gp), m_ResourceManager(ResourceManager(gp)),
m_EntityManager(EntityManager(m_ResourceManager)), m_map(Map(m_ResourceManager))
{
    for (int i = 0; i < (int)TowerType::COUNT; i++)
    {
        Vector2 position = {SCREEN_WIDTH - TILE_SIZE * (2 + i * 3) / 2, TILE_SIZE};
        m_ButtonManager.createButton(new ShopButton(gp, position,
                                                    m_ResourceManager, (TowerType)i));
    }
}

void Game::update()
{
    Vector2 mouse_pos = gpMousePosition(m_gp);

    float delta_time = get_delta_time();

    for (TowerSlot& slot : Tower::m_tower_slots)
    {  
        if (!m_ButtonManager.m_current || slot.m_is_occuped)
            continue;

        if (c_point_box(mouse_pos, slot.get_collision()))
        {
            m_money -= m_ButtonManager.m_current->get_price();
            slot.m_is_occuped = true;
            switch (m_ButtonManager.m_current->get_type())
            {
                case TowerType::STANDARD:
                    m_EntityManager.createTower(new StandardTower(&slot, m_ResourceManager));
                    break;

                case TowerType::SLOWING:
                    m_EntityManager.createTower(new SlowingTower(&slot, m_ResourceManager));
                    break;

                case TowerType::EXPLOSIVE:
                    m_EntityManager.createTower(new ExplosiveTower(&slot, m_ResourceManager));
                    break;
            }
            m_ButtonManager.m_current->is_undragged();
        }
    }

    m_ButtonManager.update();
    
    m_EntityManager.update(delta_time);

    // To put in the entity manager
    for (Tower* tower : m_EntityManager.m_towers)
    {
        if (!tower)
                continue;

        tower->update(delta_time);

        if (gpMouseButtonIsPressed(m_gp, GP_MOUSE_BUTTON_2))
        {
            if (c_point_box(tower->get_position(), Rectangle{mouse_pos, 32, 32}))
                tower->m_should_destroy = true;
        }
    }

    m_EntityManager.clear();
}

void Game::display() const
{   
    m_map.draw(m_gp);
    
    m_EntityManager.draw(m_gp);

    m_hud.draw(m_gp);

    m_ButtonManager.draw(m_gp);

    std::string wave_string = "Wave " + std::to_string(m_EntityManager.get_wave_index()) +
                              "/" + std::to_string(m_EntityManager.get_wave_count()) + " - ";
    
    int timer = m_EntityManager.get_timer();
    if (timer > 0)
        wave_string += "Next wave in: " + std::to_string(timer) + "s";
    else
    {
        int enemy_count = m_EntityManager.get_enemy_count();
        wave_string += std::to_string(enemy_count) + (enemy_count > 1 ? " enemies" : " enemy") + " left";
    }

    gpDrawTextAligned(m_gp, m_ResourceManager.get_font(), {SCREEN_WIDTH / 2, 25},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, wave_string.c_str());

    std::string money_string = "Money " + std::to_string(m_money) + "$";
    gpDrawTextAligned(m_gp, m_ResourceManager.get_font(), {SCREEN_WIDTH / 2, 75},
                      GP_CBLACK, GP_TEXTALIGN_CENTER, money_string.c_str());
}

float Game::get_delta_time()
{
    if (gpKeyIsPressed(m_gp, GP_KEY_P))
        m_isPaused = !m_isPaused;

    if (gpKeyIsPressed(m_gp, GP_KEY_LEFT) && m_game_speed > 0)
        m_game_speed -= 0.5f;

    if (gpKeyIsPressed(m_gp, GP_KEY_RIGHT))
        m_game_speed += 0.5f;

    return gpGetFrameTime(m_gp) * (m_isPaused ? 0 : m_game_speed);
}