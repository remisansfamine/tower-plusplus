#pragma once

#include "enemy.h"
#include "tower.h"
#include "ressource_manager.h"
#include <vector>

class Game
{
    private:
        float   m_game_speed = 1.f;
        int     m_money;

        GPLib* gp;
        const RessourceManager RM;

        std::vector<Enemy*> enemies;
        std::vector<Tower*> towers;

    public:
        Game(GPLib* gp) : gp(gp), RM(RessourceManager(gp)) { }


        float   delta_time = 0;
        void    update();

        void    display();
};