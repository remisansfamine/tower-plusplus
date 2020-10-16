#pragma once

#include "resource_manager.h"
#include "tower.h"

class StandardTower : public Tower
{
    public:
        StandardTower(TowerSlot* slot, const ResourceManager& RM);

        void createBullet() override;
};