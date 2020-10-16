#pragma once

#include "enemy.h"

class WeakEnemy : public Enemy
{
    public:
        WeakEnemy(Vector2 position, const ResourceManager& RM);
        void update(float deltaTime) override;
};