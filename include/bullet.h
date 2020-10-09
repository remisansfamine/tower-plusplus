#pragma once

#include "enemy.h"
#include "entity.h"

class Bullet : public Entity
{
    private:
        float   m_speed;
        
    public:
        Enemy*  m_target = nullptr;

        Bullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM);

        void update(float delta_time) override;

        void move(float delta_time);
};