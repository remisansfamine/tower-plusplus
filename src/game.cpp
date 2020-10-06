#include <cmath>


#include <iostream>
#include <algorithm>

#include "game.h"
#include "tower.h"
#include "enemy.h"

#include <gp/gp.h>

void Game::update()
{
    //std::cout << gpGetFrameTime(gp) << std::endl;
    GPVector2 mouse_pos = gpMousePosition(gp);

    if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_1))
    {
        towers.push_back(new Tower(mouse_pos.x, mouse_pos.y, 50, 50, RM));
    }
    
        for (Tower* tower : towers)
        {
            if (gpMouseButtonIsPressed(gp, GP_MOUSE_BUTTON_2))
            {
                    if (sqrt(powf(mouse_pos.x - tower->X(), 2) + powf(mouse_pos.y - tower->Y(), 2)) < 100)
                    {
                        tower = towers.back();
                        towers.pop_back();
                        delete tower;
                    }
            }
        }
}

void Game::display()
{   
    for (Tower* tower : towers)
    {
        std::cout << "x: " << tower->X() << " y: " << tower->Y() << std::endl;
        gpDrawTexture(gp, tower->get_texture(), GPVector2{tower->X(), tower->Y()}, true, GPColor{1, 1, 1, 1});
    }
}