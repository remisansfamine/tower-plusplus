#pragma once

#include "tower.h"

class ExplosiveTower : public Tower
{
    public:
        ExplosiveTower(Vector2 position, const ResourceManager& RM);
        
        void update() override;
};