#pragma once

#include "enemy.h"

class HealerEnemy : public Enemy
{
    public:
        HealerEnemy(Vector2 position, const ResourceManager& RM);
    
        void update(float delta_time) override;
};