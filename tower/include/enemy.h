#pragma once

#include "entity.h"
#include "resource_manager.h"

#include <vector>
#include <array>

class Enemy : public Entity
{
    protected:
        float   m_speed;
        int     m_current_waypoint = 0;
        int     m_reward;
        
    public:
        //static  std::vector<Vector2> m_waypoints;
        static  std::array<Vector2, 26> m_waypoints;

        Enemy(Vector2 position);

        void    move(float delta_time);

        int     get_reward() const;
};