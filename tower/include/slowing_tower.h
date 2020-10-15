#pragma once

#include "tower.h"

class SlowingTower : public Tower
{
    public:
        SlowingTower(Vector2 position, const ResourceManager& RM);

        void create_bullet() override;
};