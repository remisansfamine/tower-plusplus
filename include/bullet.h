#pragma once

#include "enemy.h"
#include "entity.h"

class Bullet : public Entity
{
    private:
        float   m_speed;
        
    public:
        float   m_angle;

        Enemy*  m_target = nullptr;

        Bullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM);

        void update(float delta_time) override;

        virtual bool collision_check(const Enemy&) const;

        void move(float delta_time);

        virtual void hit(Enemy&);
};