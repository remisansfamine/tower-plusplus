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
    STANDARD_BULLET,
    SLOWING_BULLET,
    EXPLOSIVE_BULLET,
    GRASS,
    PATH_EAST,
    PATH_NORTH,
    PATH_C_LB,
    PATH_C_ULRB,
    PATH_C_RB,
    PATH_C_UL,
    PATH_C_UR,
    CASTLE,

    ERROR
};

class ResourceManager
{
    private:
        GPFont      m_font;
        GPTexture   m_textures[(unsigned int)TextureType::ERROR];
        GPLib*      m_gp;

    public:
        ResourceManager(GPLib* gp);

        ~ResourceManager();
        const GPTexture get_texture(TextureType type) const;
        const GPFont    get_font() const;
};