#pragma once

#include <gp/gp.h>
#include "resource_manager.h"
#include "enemy.h"
#include "tower.h"
#include <fstream>

#define MAP_WIDTH 15
#define MAP_HEIGHT 10
#define TILE_SIZE 80

class Map
{
    private:
        GPTexture m_tiles[MAP_WIDTH][MAP_HEIGHT];
        
        void    generateMap(const ResourceManager& RM);

        void    interpretTile(const ResourceManager& RM, int hor_index, int vert_index, char current);

    public:
        Map(const ResourceManager& RM);

        const GPTexture get_texture(unsigned int hor_index, unsigned int vert_index) const;
};