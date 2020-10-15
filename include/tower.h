#pragma once

#include "tower_slot.h"
#include "entity.h"

#include <vector>

enum class TowerType : unsigned int
{
    EXPLOSIVE = 0,
    SLOWING = 1,
    STANDARD = 2,

    COUNT = 3
};

class Enemy;

class Tower : public Entity
{
    protected:
        Enemy*  m_target = nullptr;
        float   m_fire_rate;
        float   m_cooldown;
        float   m_range;
        
    public:
        TowerSlot*  m_slot = nullptr;
        static std::vector<TowerSlot> m_tower_slots;

        Tower(TowerSlot* slot);

        virtual void update(float delta_time);

        void get_target();

        void shoot();

        virtual void create_bullet() = 0;

        void draw(GPLib* gp) override;
};