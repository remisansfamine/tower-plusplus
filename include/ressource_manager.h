#pragma once

#include <gp/gp.h>

#include <iostream>

enum class TextureType : unsigned int
{
    TOWER_IDLE = 0,
    ENEMY_IDLE = 1,
    BULLET = 2
};

class RessourceManager
{
    private:
        GPTexture textures[7];
        GPLib* gp;

    public:
        RessourceManager(GPLib* gp) : gp(gp)
        {
            textures[(int)TextureType::TOWER_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/tower.jpg"));
            textures[(int)TextureType::ENEMY_IDLE] = GPTexture(gpTextureLoadFromFile(gp, "media/enemy.png"));
            textures[(int)TextureType::BULLET] = GPTexture(gpTextureLoadFromFile(gp, "media/bullet.jpg"));
        }

        ~RessourceManager()
        {
            for (GPTexture texture : textures)
                gpTextureUnload(gp, texture);
        }

        const GPTexture get_texture(unsigned int index) const { return textures[index]; }
};