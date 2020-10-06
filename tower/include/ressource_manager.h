#pragma once

#include <gp/gp.h>

class RessourceManager
{
    private:
        GPTexture textures[7];

    public:
        RessourceManager(GPLib* gp)
        {
            textures[0] = GPTexture(gpTextureLoadFromFile(gp, "media/tower.jpg"));
        }

        const GPTexture get_texture(unsigned int index) const { return textures[index]; }
};