#pragma once

#include "resource_manager.h"
#include "tower.h"

class ExplosiveTower : public Tower
{
    public:
        ExplosiveTower(TowerSlot* slot, const ResourceManager& RM);
        
        void createBullet() override;
};