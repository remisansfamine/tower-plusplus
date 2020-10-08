#pragma once

#include <gp/gp.h>

#include <iostream>

enum class TextureType : unsigned int
{
    TOWER_IDLE,
    TOWER_SLOT,
    ENEMY_IDLE,
    BULLET,
    PATH,
    GRASS,

    ERROR
};

class RessourceManager
{
    private:
        GPTexture textures[7];
        GPLib* gp;

    public:
        RessourceManager(GPLib* gp);

        ~RessourceManager();
        const GPTexture get_texture(unsigned int index) const;
};