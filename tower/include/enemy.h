#pragma once

#include "entity.h"
#include "resource_manager.h"

#include <vector>

class Enemy : public Entity
{
    protected:
        int     m_currentWaypoint = 0;
        int     m_libebarOffset = 5;
        int     m_reward;
        float   m_stunCooldown = 0.f;
        float   m_speed;
        Rectangle   m_rect = {{0, 0}, 32, 32};

        void    move(float delta_time);

        void    reachCastle();

    public:
        static std::vector<Vector2>  m_waypoints;

        Enemy(Vector2 position);

        virtual void    update(float delta_time);

        int     getReward() const;

        Rectangle   getRect() const;

        float   getHalfsize() const;

        void    stun(float);

        virtual void draw(GPLib* gp) override;
};