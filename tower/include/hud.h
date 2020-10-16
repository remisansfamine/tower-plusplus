#pragma once

#include <gp/gp.h>
#include "entity_manager.h"


class HUD
{
    private:
        EntityManager* m_entityManager;

        void    displayWavesState(GPLib* gp) const;

    public:
        HUD(EntityManager*);

        void    draw(GPLib* gp) const;
};