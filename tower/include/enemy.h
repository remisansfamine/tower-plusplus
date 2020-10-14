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
        int     m_libebar_offset = 5;
        float   m_stun_cooldown = 0;
        Rectangle   m_rect = {{0, 0}, 32, 32};
        
    public:
        static std::array<Vector2, 26>  m_waypoints;
        static int                      m_waypoints_count;

        Enemy(Vector2 position);

        virtual void    update(float delta_time);

        void    move(float delta_time);

        int     get_reward() const;

        Rectangle   get_rect() const;

        float   get_halfsize() const;

        int     get_lifebar_offert() const;

        void    stun(float);
};