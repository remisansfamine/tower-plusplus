#pragma once

#include "enemy.h"
#include "entity.h"

class Bullet : public Entity
{
    protected:
        float   m_speed;
        float   m_angle;
        Enemy*  m_target = nullptr;

        void move(float delta_time);

        virtual void hit(Enemy&);

    public:
        Bullet(Vector2 position, Enemy* enemy);

        void update(float delta_time) override;

        void draw(GPLib* gp) override;
};