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

class ResourceManager
{
    private:
        GPTexture textures[7];
        GPLib* gp;

    public:
        ResourceManager(GPLib* gp);

        ~ResourceManager();
        const GPTexture get_texture(unsigned int index) const;
};