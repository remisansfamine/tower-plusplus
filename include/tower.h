#pragma once

#include "game.h"
#include "entity.h"

#include <gp/gp.h>

#include "ressource_manager.h"


class Tower : public Entity
{
    protected:
        float   m_fire_rate;
        int     m_cost;

    public:
        Tower(float x, float y, float life, float fire_rate, const RessourceManager& RM) : Entity(x, y, life), m_fire_rate(fire_rate)
        {
          //  texture = game.get_texture(0);
          texture = RM.get_texture(0);
              //texture = GPTexture(gpTextureLoadFromFile(gp, "media/tower.jpg"));
        }

       // void update() override;

};