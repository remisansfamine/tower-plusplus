#include <cmath>

#include <iostream>
#include <algorithm>

#include "maths.h"

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

    if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1))
        towers.push_back(new ExplosiveTower(mouse_pos, RM));

    if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_3))
        enemies.push_back(new StrongEnemy(mouse_pos, RM));

    for (Enemy* enemy : enemies)
    {
        enemy->update();
    }

    for (Tower* tower : towers)
    {
        tower->update();

        if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_2))
        {
            if (tower->get_position().get_distance(mouse_pos) < 100)
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
        std::cout << tower->get_position().x << std::endl;
        gpDrawTexture(gp, tower->get_texture(), GPVector2(tower->get_position()), true, GPColor{1, 1, 1, 1});
    }

    for (Enemy* enemy : enemies)
    {
        gpDrawTexture(gp, enemy->get_texture(), GPVector2(enemy->get_position()), true, GPColor{1, 1, 1, 1});
    }
}