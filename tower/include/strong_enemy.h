#pragma once

#include "enemy.h"
#include <iostream>

class StrongEnemy : public Enemy
{
    public:
        StrongEnemy(Vector2 position, const ResourceManager& RM);
        
        void update(float delta_time) override;
};