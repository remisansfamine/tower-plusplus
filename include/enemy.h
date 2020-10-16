#pragma once

#include "entity.h"
#include "resource_manager.h"

#include <vector>

class Enemy : public Entity
{
    protected:
        float   m_speed;
        int     m_currentWaypoint = 0;
        int     m_reward;
        int     m_libebarOffset = 5;
        float   m_stunCooldown = 0;
        Rectangle   m_rect = {{0, 0}, 32, 32};

        void    move(float delta_time);

    public:
        static std::vector<Vector2>  m_waypoints;

        Enemy(Vector2 position);

        virtual void    update(float delta_time);

        int     getReward() const;

        Rectangle   getRect() const;

        float   getHalfsize() const;

        void    stun(float);

        virtual void draw(GPLib* gp) override;

        void    reachCastle();
};