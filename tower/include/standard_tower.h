#pragma once

#include "tower.h"

class StandardTower : public Tower
{
    public:
        StandardTower(Vector2 position, const ResourceManager& RM);

        void create_bullet() override;
};