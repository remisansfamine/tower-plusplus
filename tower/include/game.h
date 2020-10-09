#pragma once

#include "map.h"
#include "resource_manager.h"
#include "render_manager.h"
#include "entity_manager.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

class Game
{
    private:
        bool    m_isPaused = false;
        float   m_game_speed = 1;
        float   m_spawn_rate = 10;
        float   m_spawn_rate_modifier = 2;
        float   m_spawn_cooldown;
        int     m_money;

        GPLib* gp;
        const ResourceManager   m_ResourceManager;
        RendererManager         m_RendererManager;
        EntityManager           m_EntityManager;
        Map                     m_map;

    public:
        Game(GPLib* gp);

        void    start();

        void    update();

        void    display() const;
};