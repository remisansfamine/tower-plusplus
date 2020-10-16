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
        GPTexture   m_upgrades_texture[2];
        Enemy*      m_target = nullptr;
        int         m_level = 0;
        float       m_fireRate;
        float       m_cooldown;
        float       m_range;
        
        void    getTarget();
        void    shoot();

        virtual void upgrade();

        virtual void    createBullet() = 0;

    public:
        int         m_price;
        TowerSlot*  m_slot = nullptr;
        static std::vector<TowerSlot> m_towerSlots;

        Tower(TowerSlot* slot);
        ~Tower();

        virtual void update(float deltaTime, GPLib* gp);

        void draw(GPLib* gp) override;
};