#pragma once

#include "entity.h"
#include "ressource_manager.h"

class Enemy : public Entity
{
    protected:
        float   m_speed;
        int     m_current_waypoint = 0;
        
    public:
        static  std::vector<Vector2> m_waypoints;

        Enemy(Vector2 position) : Entity(position) { }

        void move()
        {
            if (m_current_waypoint == m_waypoints.size())
                return;
                
            m_direction = (m_waypoints[m_current_waypoint] - m_position).normalize();
            if (m_position.get_distance(m_waypoints[m_current_waypoint]) <= 10)
                m_current_waypoint++;

            m_position += m_direction * m_speed * delta_time;
        }
};