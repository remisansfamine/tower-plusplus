#pragma once

#include <gp/gp.h>

#include <iostream>

enum class TextureType : unsigned int
{
    STANDARD_IDLE,
    SLOWING_IDLE,
    EXPLOSIVE_IDLE,
    TOWER_SLOT,
    WEAK_ENEMY_IDLE,
    HEALER_ENEMY_IDLE,
    STRONG_ENEMY_IDLE,
    BULLET,
    GRASS,
    PATH_EAST,
    PATH_NORTH,
    PATH_C_LB,
    PATH_C_ULRB,
    PATH_C_RB,
    PATH_C_UL,
    PATH_C_UR,
    BUTTON,

    ERROR
};

class ResourceManager
{
    private:
        GPTexture textures[(unsigned int)TextureType::ERROR];
        GPLib* gp;

    public:
        ResourceManager(GPLib* gp);

        ~ResourceManager();
        const GPTexture get_texture(TextureType type) const;
};