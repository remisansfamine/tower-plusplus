#include <fstream>

#include "map.h"
#include "enemy.h"

void    Map::generateTilemap(const ResourceManager& RM)
{
    std::ifstream infile("media/tilemap.txt");
    int hor_index = 0, vert_index = 0;

    char current;
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
        
        case '-':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_EAST);
            break;

        case '|':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_NORTH);
            break;

        case '+':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_C_ULRB);
            break;

        case '@':
            Tower::m_tower_slots.push_back(new TowerSlot(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2)));
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::TOWER_SLOT);
            break;
        
        case '1':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_C_LB);
            break;

        case '2':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_C_RB);
            break;

        case '3':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_C_UL);
            break;

        case '4':
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::PATH_C_UR);
            break;

        default:
            m_tiles[hor_index][vert_index] = RM.get_texture(TextureType::ERROR);       
    }
}

Map::Map(const ResourceManager& RM)
{
    generateTilemap(RM);
    generateWaypoints();
}

void    Map::generateWaypoints() const
{
    std::ifstream infile("media/waypoint.txt");
    int hor_index = 0, vert_index = 0;

    char current, last = 0;
    while (infile >> current)
    {
        if (hor_index == MAP_WIDTH)
        {
            hor_index = 0;
            vert_index++;
        }
        
        if (current >= 'A' && current <= 'Z')
        {
            if (current > last)
                last = current;

            Enemy::m_waypoints[current - 'A'] = Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2);
        }
        hor_index++;
    }

    if (last >= 'A')
        Enemy::m_waypoints_count = last - 'A' + 1;
}

const GPTexture Map::get_texture(unsigned int hor_index, unsigned int vert_index) const
{
    return m_tiles[hor_index][vert_index];
}