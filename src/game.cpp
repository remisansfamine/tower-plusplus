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
: gp(gp), m_ResourceManager(ResourceManager(gp)), m_map(Map(m_ResourceManager)), m_EntityManager(EntityManager(m_ResourceManager))
{
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE * 4, TILE_SIZE}, m_ResourceManager, TowerType::STANDARD));
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE * 5 / 2, TILE_SIZE}, m_ResourceManager, TowerType::SLOWING));
    m_ButtonManager.createButton(new ShopButton(gp, {SCREEN_WIDTH - TILE_SIZE, TILE_SIZE}, m_ResourceManager, TowerType::EXPLOSIVE));
}

void Game::update()
{
    GPVector2 mouse_pos = gpMousePosition(gp);

    if (gpKeyIsPressed(gp, GP_KEY_P))
        m_isPaused = !m_isPaused;

    if (gpKeyIsPressed(gp, GP_KEY_LEFT) && m_game_speed > 0)
        m_game_speed -= 0.5f;

    if (gpKeyIsPressed(gp, GP_KEY_RIGHT))
        m_game_speed += 0.5f;

    float delta_time = gpGetFrameTime(gp) * (m_isPaused ? 0 : m_game_speed);

    for (TowerSlot& slot : Tower::m_tower_slots)
    {  
        if (!m_ButtonManager.m_current || slot.m_isOccuped)
            continue;

        if (c_point_box(mouse_pos, slot.get_collision()))
        {
            m_money -= m_ButtonManager.m_current->get_price();
            slot.m_isOccuped = true;
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
        }
    }

    for (Button* button : m_ButtonManager.m_buttons)
    {
        if (!button)
            continue;

        button->update();
    }
    
    m_EntityManager.update(delta_time);

    for (Enemy* enemy : m_EntityManager.m_enemies)
    {
        if (!enemy)
            continue;

        enemy->update(delta_time);

        if (enemy->m_life.m_life <= 0)
        {
            m_money += enemy->get_reward();
            m_EntityManager.destroyEnemy(enemy);
        }
    }

    for (Bullet* bullet : m_EntityManager.m_bullets)
    {
        if (!bullet)
            continue;

        bullet->update(delta_time);

        for (Enemy* enemy : m_EntityManager.m_enemies)
        {
            if (!enemy)
                continue;

            if (c_point_box(bullet->get_position(), Rectangle{enemy->get_position(), enemy->get_halfsize(), enemy->get_halfsize()}))
            {
                enemy->m_life.m_life -= bullet->get_damage();

                m_EntityManager.destroyBullet(bullet);
            }
        }

        if (bullet->m_target->m_life.m_life <= 0)
            m_EntityManager.destroyBullet(bullet);
    }
    
    for (Tower* tower : m_EntityManager.m_towers)
    {
        if (!tower)
                continue;

        if (!tower->m_target)
        {
            for (Enemy* enemy : m_EntityManager.m_enemies)
            {
                if (!enemy)
                    continue;

                if (c_circle_point({tower->m_range, tower->get_position()}, enemy->get_position()))
                {
                    tower->m_target = enemy;
                    break;
                }
            }
        }
        else
        {
            if (c_circle_point({tower->m_range, tower->get_position()}, tower->m_target->get_position()) &&
            tower->m_target->m_life.m_life > 0)
            {
                Vector2 vect = tower->m_target->get_position() - tower->get_position();

                tower->m_angle = atan2(vect.y, vect.x) + M_PI / 2;

                if (tower->m_cooldown <= 0)
                {
                    m_EntityManager.createBullet(new Bullet(tower->get_position(),
                                                                tower->m_target, tower->get_damage(),
                                                                m_ResourceManager));

                    tower->m_cooldown = tower->m_fire_rate;
                }
            }
            else
                tower->m_target = nullptr;
        }

        tower->update(delta_time);

        if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_2))
        {
            if (c_point_box(tower->get_position(), Rectangle{mouse_pos, 32, 32}))
            {
                m_EntityManager.destroyTower(tower);
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

        if (!tower)
                continue;

        gpDrawTextureEx(gp, tower->get_texture(), {64, 64}, tower->get_position(), tower->m_angle, {1, 1}, nullptr, GPColor{1, 1, 1, 1});

        gpDrawCircle(gp, tower->get_position(), tower->m_range, GPColor{1, 0, 0, 1});
    }

    for (Bullet* bullet : m_EntityManager.m_bullets)
    {
        if (!bullet)
                continue;

        gpDrawTextureEx(gp, bullet->get_texture(), {64, 64}, bullet->get_position(), bullet->m_angle, {1, 1}, nullptr, GPColor{1, 1, 1, 1});
    }

    for (Enemy* enemy : m_EntityManager.m_enemies)
    {
        if (!enemy)
            continue;

        gpDrawTexture(gp, enemy->get_texture(), enemy->get_position(), true, GPColor{1, 1, 1, 1});
        
        if (enemy->m_life.m_life >= enemy->m_life.get_max_life())
            continue;

        GPRect lifebar = {enemy->get_position().x - enemy->get_halfsize(), enemy->get_position().y + enemy->get_halfsize() + enemy->get_lifebar_offert(), enemy->get_halfsize() * 2, enemy->get_halfsize() / 4};
        gpDrawRectFilled(gp, lifebar, GPColor{1, 1, 1, 1});

        lifebar.w *= enemy->m_life.m_life / enemy->m_life.get_max_life();
        gpDrawRectFilled(gp, lifebar, GPColor{1, 0, 0, 1});

        lifebar.w /= enemy->m_life.m_life / enemy->m_life.get_max_life();
        gpDrawRect(gp, lifebar, GPColor{0, 0, 0, 1});
    }

    for (Button* button : m_ButtonManager.m_buttons)
    {
        if (!button)
                continue;

        gpDrawTexture(gp, button->m_texture, button->m_rect.position, true, button->m_color);
    }

    m_RendererManager.draw(gp);
}