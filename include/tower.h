#pragma once

#include "tower_slot.h"
#include "entity.h"

#include <vector>

#include "resource_manager.h"

enum class TowerType
{
    STANDARD,
    SLOWING,
    EXPLOSIVE
};

class Enemy;

class Tower : public Entity
{
    protected:
        Enemy*  m_target = nullptr;
        float   m_fire_rate;
        float   m_cooldown;
        float   m_range;
        float   m_angle;
    public:
        static std::vector<TowerSlot> m_tower_slots;

        Tower(Vector2 position);

        virtual void update(float delta_time);

        void get_target();

        void shoot();

        virtual void create_bullet() = 0;

        void draw(GPLib* gp) override;
};