#pragma once

#include <gp/gp.h>
#include "ressource_manager.h"
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

    public:
        Map(const RessourceManager& RM)
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
                
                case 'O':
                    Tower::tower_slots.push_back(TowerSlot(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2)));
                    m_tiles[hor_index][vert_index] = RM.get_texture((unsigned int)TextureType::TOWER_SLOT);
                    break;
                
                default:
                    if (current >= '0' && current <= '9')
                    {
                        //std::cout <<  << std::endl;
                        m_tiles[hor_index][vert_index] = RM.get_texture((unsigned int)TextureType::PATH);
                        Enemy::m_waypoints.push_back(Vector2(hor_index * TILE_SIZE + TILE_SIZE / 2, vert_index * TILE_SIZE + TILE_SIZE / 2));
                        break;
                    }
                    m_tiles[hor_index][vert_index] = RM.get_texture((unsigned int)TextureType::ERROR);       
            }
            hor_index++;
            }
        }

        const GPTexture get_texture(unsigned int hor_index, unsigned int vert_index) const
        {
            return m_tiles[hor_index][vert_index];
        }
};