#pragma once

#include <gp/gp.h>
#include "entity_manager.h"


class HUD
{
    private:
        GPFont m_font;

        EntityManager* m_entityManager;

        void    displayWavesState(GPLib* gp) const;

        void    drawCastleLife(GPLib*) const;

        void    drawGameOver(GPLib*) const;

    public:
        HUD(EntityManager*);

        void    draw(GPLib* gp) const;
};