#pragma once

#include "map.h"
#include "enemy.h"
#include "tower.h"
#include "ressource_manager.h"
#include <vector>
#include "bullet.h"

class Game
{
    private:
        float   m_game_speed = 3.f;
        int     m_money;

        GPLib* gp;
        const RessourceManager RM;
        Map     m_map;

        std::vector<Enemy*> enemies;
        std::vector<Tower*> towers;
        std::vector<Bullet*> bullets;

    public:
        Game(GPLib* gp) : gp(gp), RM(RessourceManager(gp)), m_map(Map(RM)) { start(); }

        void    start();

        void    update();

        void    display() const;
};