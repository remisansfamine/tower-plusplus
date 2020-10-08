#include <fstream>

#include "map.h"

#include "enemy.h"

Map::Map(const RessourceManager& RM)
{
    std::ifstream infile("media/map.txt");
    int hor_index = 0, vert_index = 0;

    char current, next;
    while (infile >> current)
    {
        if (hor_index == MAP_WIDTH)
        {
            hor_index = 0;
            vert_index++;
        }
    switch (current)
    {
        case '#':
            m_tiles[hor_index][vert_index] = RM.get_texture((unsigned int)TextureType::GRASS);
            break;
        
        default:
            if (current >= '0' && current <= '9')
            {
                m_tiles[hor_index][vert_index] = RM.get_texture((unsigned int)TextureType::PATH);
                Enemy::m_waypoints.push_back(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2));
            }
    }
    hor_index++;
    }
}

const GPTexture Map::get_texture(unsigned int hor_index, unsigned int vert_index) const
{
    return m_tiles[hor_index][vert_index];
}