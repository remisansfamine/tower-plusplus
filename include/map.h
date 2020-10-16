#pragma once

#include <gp/gp.h>
#include "resource_manager.h"
#include "define.h"

class Map
{
    private:
        GPTexture m_tiles[MAP_WIDTH][MAP_HEIGHT];
        
        void    generateTilemap(const ResourceManager& RM);

        void    generateWaypoints(const ResourceManager& RM);

        void    interpretTile(const ResourceManager& RM, int hor_index, int vert_index, char current);

    public:
        Map(const ResourceManager& RM);

        void draw(GPLib* gp) const;
};