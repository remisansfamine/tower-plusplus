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

#include <gp/gp.h>

void Game::update()
{
    GPVector2 mouse_pos = gpMousePosition(gp);

    float delta_time = gpGetFrameTime(gp);

    if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1))
        towers.push_back(new ExplosiveTower(mouse_pos, RM));

    if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_3))
        enemies.push_back(new StrongEnemy(mouse_pos, RM));

    for (Enemy* enemy : enemies)
    {
        enemy->delta_time = delta_time;
        enemy->update();

        if (enemy->m_life.m_life <= 0)
        {
            *enemy = *enemies.back();
            enemies.pop_back();

            // if (enemies.size() > 1)
            //     delete enemies.back(); // Do segfault
        }
    }

    for (Bullet* bullet : bullets)
    {
        bullet->delta_time = delta_time;
        bullet->update();

        for (Enemy* enemy : enemies)
        {
            if (c_point_box(bullet->get_position(), Rectangle{enemy->get_position(), 50, 50}))
            {
                enemy->m_life.m_life -= bullet->get_damage();

                *bullet = *bullets.back();
                bullets.pop_back();

                // if (bullets.size() > 1)
                //     delete bullets.back(); // Do segfault
            }
        }

        if (!bullet->m_target)
        {
            *bullet = *bullets.back();
            bullets.pop_back();

            // if (bullets.size() > 1)
            //     delete bullets.back(); // Do segfault
        }
    }

    for (Tower* tower : towers)
    {
        tower->delta_time = delta_time;
        for (Enemy* enemy : enemies)
        {
            if (c_circle_point({tower->m_range, tower->get_position()}, enemy->get_position()))
            {
                if (tower->m_cooldown <= 0)
                {
                    bullets.push_back(new Bullet(tower->get_position(), enemy, tower->get_damage(), RM));
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
                    *tower = *towers.back();
                    towers.pop_back();

                    if (towers.size() > 1)
                        delete towers.back();
                }
            }
        }
    }
}

void Game::display() const
{   
    for (Tower* tower : towers)
    {
        gpDrawTexture(gp, tower->get_texture(), GPVector2(tower->get_position()), true, GPColor{1, 1, 1, 1});
    }

    for (Bullet* bullet : bullets)
            gpDrawTexture(gp, bullet->get_texture(), GPVector2(bullet->get_position()), true, GPColor{1, 1, 1, 1});

    for (Enemy* enemy : enemies)
    {
        gpDrawTexture(gp, enemy->get_texture(), GPVector2(enemy->get_position()), true, GPColor{1, 1, 1, 1});
    }
}