#include <fstream>

#include "map.h"
#include "enemy.h"
#include "castle.h"
#include "entity_manager.h"

#include "tower.h"
#include <fstream>

#include "define.h"
#include <cassert>

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

void    Map::interpretTile(const ResourceManager& RM,
                           int hor_index, int vert_index, char current)
{
    switch (current)
    {
        case '#':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::GRASS);
            break;
        
        case '-':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_EAST);
            break;

        case '|':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_NORTH);
            break;

        case '+':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_C_ULRB);
            break;

        case '@':
            Tower::m_towerSlots.push_back(TowerSlot(Vector2(hor_index * TILE_SIZE +
                                                    TILE_SIZE / 2, vert_index * TILE_SIZE +
                                                    TILE_SIZE / 2)));
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::TOWER_SLOT);
            break;
        
        case '1':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_C_LB);
            break;

        case '2':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_C_RB);
            break;

        case '3':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_C_UL);
            break;

        case '4':
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::PATH_C_UR);
            break;

        default:
            m_tiles[hor_index][vert_index] = RM.getTexture(TextureType::ERROR);       
    }
}

Map::Map(const ResourceManager& RM)
{
    generateTilemap(RM);
    generateWaypoints(RM);
}

void    Map::generateWaypoints(const ResourceManager& RM)
{
    std::ifstream infile("media/waypoint.txt");
    int horIndex = 0, vertIndex = 0;
    int lastHorIndex = 0, lastVertIndex = 0;
    char current, last = 0;
    while (infile >> current)
    {
        if (horIndex == MAP_WIDTH)
        {
            horIndex = 0;
            vertIndex++;
        }
        
        if (current >= 'A' && current <= 'Z')
        {
            if (current > last)
            {
                lastHorIndex = horIndex;
                lastVertIndex = vertIndex;
                last = current;
            }

            Enemy::m_waypoints[current - 'A'] = Vector2(horIndex * TILE_SIZE + TILE_SIZE / 2,
                                                        vertIndex * TILE_SIZE + TILE_SIZE / 2);
        }
        horIndex++;
    }

    assert(last >= 'B');
    Enemy::m_waypoints.resize(last - 'A' + 1);

    m_tiles[lastHorIndex][lastVertIndex] = RM.getTexture(TextureType::CASTLE);
}

void Map::draw(GPLib* gp) const
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            gpDrawTexture(gp, m_tiles[i][j], {(float)TILE_SIZE * i, (float)TILE_SIZE * j},
                         false, GP_CWHITE);
        }
    }
}
