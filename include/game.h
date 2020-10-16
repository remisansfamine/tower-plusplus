#pragma once

#include "map.h"
#include "resource_manager.h"
#include "entity_manager.h"
#include "button_manager.h"
#include "hud.h"

class Game
{
    private:
        bool    m_isPaused = false;
        float   m_gameSpeed = 1;

        GPLib* m_gp;
        const ResourceManager   m_resourceManager;
        EntityManager           m_entityManager;
        ButtonManager           m_buttonManager;
        Map                     m_map;
        HUD                     m_hud;

    public:
        static int  m_money;

        Game(GPLib* gp);

        void    start();

        void    update();

        void    display() const;

        float   getDeltaTime();
};