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

#include <gp/gp.h>

std::vector<Vector2> Enemy::m_waypoints;
std::vector<TowerSlot> Tower::tower_slots;

void Game::start()
{
    m_spawn_cooldown = m_spawn_rate;
}

void Game::update()
{
    GPVector2 mouse_pos = gpMousePosition(gp);

    if (gpKeyIsPressed(gp, GP_KEY_P))
        m_isPaused = !m_isPaused;

    float delta_time = gpGetFrameTime(gp) * (m_isPaused ? 0 : m_game_speed);

    if (gpKeyIsPressed(gp, GP_KEY_L))
    {
        m_EntityManager.createButton(new Button(gp, mouse_pos, m_ResourceManager));
    }

    int count = 0;
    for (TowerSlot slot : Tower::tower_slots)
    {  
        if (c_point_box(mouse_pos, slot.get_collision()))
        {
            if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1) && !slot.m_isOccuped)
            {
                m_EntityManager.createTower(new SlowingTower(slot.get_position(), m_ResourceManager));
                slot.m_isOccuped = true;
            }
        }
    }

    for (Button* button : m_EntityManager.m_buttons)
    {
        button->update();
    }
    
    m_spawn_cooldown -= delta_time;

    if (m_spawn_cooldown <= 0 || gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_3))
    {
        m_spawn_cooldown = m_spawn_rate;
        m_spawn_rate -= delta_time * 2;
        m_EntityManager.createEnemy(new StrongEnemy(Enemy::m_waypoints[0], m_ResourceManager));
    }

    for (Enemy* enemy : m_EntityManager.m_enemies)
    {
        enemy->delta_time = delta_time;
        enemy->update();

        if (enemy->m_life.m_life <= 0)
        {
            m_EntityManager.destroyEnemy(enemy);
        }
    }

    for (Bullet* bullet : m_EntityManager.m_bullets)
    {
        bullet->delta_time = delta_time;
        bullet->update();

        for (Enemy* enemy : m_EntityManager.m_enemies)
        {
            if (c_point_box(bullet->get_position(), Rectangle{enemy->get_position(), 50, 50}))
            {
                enemy->m_life.m_life -= bullet->get_damage();

                m_EntityManager.destroyBullet(bullet);

            }
        }

        if (!bullet->m_target)
        {
            m_EntityManager.destroyBullet(bullet);
        }
    }
    
    for (Tower* tower : m_EntityManager.m_towers)
    {
        tower->delta_time = delta_time;
        for (Enemy* enemy : m_EntityManager.m_enemies)
        {
            if (c_circle_point({tower->m_range, tower->get_position()}, enemy->get_position()))
            {
                if (tower->m_cooldown <= 0)
                {
                    m_EntityManager.createBullet(new Bullet(tower->get_position(),
                                                            enemy, tower->get_damage(),
                                                            m_ResourceManager));

                    tower->m_cooldown = tower->m_fire_rate;
                }
            }
        }

        tower->update();

        if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_2))
        {
            if (c_point_box(tower->get_position(), Rectangle{mouse_pos, 65, 65}))
            {
                tower->m_life.m_life -= 10;

                if (tower->m_life.m_life <= 0)
                {
                    m_EntityManager.destroyTower(tower);
                }
            }
        }
    }
}

void Game::display() const
{   

    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            gpDrawTexture(gp, m_map.get_texture(i, j), GPVector2{(float)TILE_SIZE * i, (float)TILE_SIZE * j}, false, GPColor{1, 1, 1, 1});
        }
    }

    for (Tower* tower : m_EntityManager.m_towers)
    {
        gpDrawTexture(gp, tower->get_texture(), GPVector2(tower->get_position()), true, GPColor{1, 1, 1, 1});
    }

    for (Bullet* bullet : m_EntityManager.m_bullets)
    {
        gpDrawTexture(gp, bullet->get_texture(), GPVector2(bullet->get_position()), true, GPColor{1, 1, 1, 1});
    }

    for (Enemy* enemy : m_EntityManager.m_enemies)
    {
        gpDrawTexture(gp, enemy->get_texture(), GPVector2(enemy->get_position()), true, GPColor{1, 1, 1, 1});
    }

    for (Button* button : m_EntityManager.m_buttons)
    {
        gpDrawTexture(gp, button->m_texture, GPVector2(button->m_rect.position), true, GPColor{1, 1, 1, 1});
    }

    m_RendererManager.draw(gp);
}