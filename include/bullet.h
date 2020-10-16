#pragma once

#include "enemy.h"
#include "entity.h"

class Bullet : public Entity
{
    protected:
        float   m_speed;
        Enemy*  m_target = nullptr;

        void move(float deltaTime);

        virtual void hit(Enemy&);

    public:
        Bullet(Vector2 position, Enemy* enemy);

        void update(float deltaTime) override;

        void draw(GPLib* gp) override;
};