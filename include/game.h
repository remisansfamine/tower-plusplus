#pragma once

#include "map.h"
#include "resource_manager.h"
#include "render_manager.h"
#include "entity_manager.h"
#include "button_manager.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

class Game
{
    private:
        bool    m_isPaused = false;
        float   m_game_speed = 1;

        GPLib* m_gp;
        const ResourceManager   m_ResourceManager;
        RendererManager         m_RendererManager;
        EntityManager           m_EntityManager;
        ButtonManager           m_ButtonManager;
        Map                     m_map;

    public:
        static int  m_money;

        Game(GPLib* gp);

        void    start();

        void    update();

        void    display() const;

        float   get_delta_time();
};