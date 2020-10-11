#pragma once

#include <gp/gp.h>

#include <iostream>

enum class TextureType : unsigned int
{
    TOWER_IDLE,
    TOWER_SLOT,
    ENEMY_IDLE,
    BULLET,
    GRASS,
    PATH_EAST,
    PATH_NORTH,
    PATH_C_ULRB,
    PATH_C_LL,
    PATH_C_LR,
    PATH_C_UL,
    PATH_C_UR,
    BUTTON,

    ERROR
};

class ResourceManager
{
    private:
        GPTexture textures[7];
        GPLib* gp;

    public:
        ResourceManager(GPLib* gp);

        ~ResourceManager();
        const GPTexture get_texture(TextureType type) const;
};