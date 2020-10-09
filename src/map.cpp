#include <fstream>

#include "map.h"
#include "enemy.h"

void    Map::generateMap(const ResourceManager& RM)
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
        
        interpretTile(RM, hor_index, vert_index, current);

        hor_index++;
    }
}

void    Map::interpretTile(const ResourceManager& RM, int hor_index, int vert_index, char current)
{
    switch (current)
    {
        case '#':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::GRASS);
            break;
        
        case 'P':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH);
            break;

        case 'O':
            Tower::tower_slots.push_back(TowerSlot(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2)));
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::TOWER_SLOT);
            break;

        default:
            if (current >= '0' && current <= '9')
            {
                m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH);
                Enemy::m_waypoints.push_back(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2));
                break;
            }
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::ERROR);       
    }
}

Map::Map(const ResourceManager& RM)
{
    generateMap(RM);
}

const GPTexture Map::get_texture(unsigned int hor_index, unsigned int vert_index) const
{
    return m_tiles[hor_index][vert_index];
}