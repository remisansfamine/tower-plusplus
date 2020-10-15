#include <cmath>

#include <iostream>
#include <algorithm>

#include "maths.h"
#include "collisions.h"
#include "game.h"

#include "slowing_tower.h"
#include "explosive_tower.h"
#include "standard_tower.h"

#include "strong_enemy.h"
#include "healer_enemy.h"
#include "weak_enemy.h"

#include "bullet.h"

#include "button.h"
#include "shop_button.h"

#include <gp/gp.h>

int Game::m_money = 10;

Game::Game(GPLib* gp)
: m_gp(gp), m_ResourceManager(ResourceManager(gp)), m_EntityManager(EntityManager(m_ResourceManager)), m_map(Map(m_ResourceManager))
{
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE * 4, TILE_SIZE}, m_ResourceManager, TowerType::STANDARD));
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE * 5 / 2, TILE_SIZE}, m_ResourceManager, TowerType::SLOWING));
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE, TILE_SIZE}, m_ResourceManager, TowerType::EXPLOSIVE));
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
                    m_EntityManager.createTower(new StandardTower(slot.get_position(), m_ResourceManager));
                    break;

                case TowerType::SLOWING:
                    m_EntityManager.createTower(new SlowingTower(slot.get_position(), m_ResourceManager));
                    break;

                case TowerType::EXPLOSIVE:
                    m_EntityManager.createTower(new ExplosiveTower(slot.get_position(), m_ResourceManager));
                    break;
            }
            m_ButtonManager.m_current->is_undragged();
        }
    }

    for (Button* button : m_ButtonManager.m_buttons)
    {
        if (!button)
            continue;

        button->update();
    }
    
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

    m_ButtonManager.draw(m_gp);

    std::string wave_string = "Wave " + std::to_string(m_EntityManager.get_wave_index()) +
                              "/" + std::to_string(m_EntityManager.get_wave_count()) +
                              " - Next wave in : " +
                              std::to_string(m_EntityManager.get_timer()) + "s";

    gpDrawText(m_gp, m_ResourceManager.get_font(), {SCREEN_WIDTH / 2 - 210, 50}, GP_CBLACK, wave_string.c_str());

    std::string money_string = "Money " + std::to_string(m_money) + "$";
    gpDrawText(m_gp, m_ResourceManager.get_font(), {SCREEN_WIDTH / 2 - 50, 100}, GP_CBLACK, money_string.c_str());
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