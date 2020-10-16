#pragma once

#include "resource_manager.h"
#include "tower.h"

class SlowingTower : public Tower
{
    public:
        SlowingTower(TowerSlot* slot, const ResourceManager& RM);

        void createBullet() override;
};