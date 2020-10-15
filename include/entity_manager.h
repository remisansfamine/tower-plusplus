#pragma once

#include <vector>
#include "castle.h"

class ResourceManager;
class Enemy;
class Tower;
class Bullet;

class EntityManager
{
    private:
        std::string m_spawn_pattern;
        bool    is_in_wave = false;
        float   m_spawn_cooldown;
        float   m_spawn_rate = 1;
        float   m_wave_timer = 10;
        unsigned int    m_spawn_index = 0;
        unsigned int    m_wave_index = 1;
        unsigned int    m_wave_count = 0;

    public:
        const ResourceManager m_ResourceManager;

        EntityManager(const ResourceManager&);

        ~EntityManager();

        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;

        Castle                  m_castle;

        void    update(float delta_time);

        void    spawn_enemies();

        void    createTower(Tower*);
        void    createEnemy(Enemy*);
        void    createBullet(Bullet*);

        void    destroyTower(Tower*);
        void    destroyEnemy(Enemy*);
        void    destroyBullet(Bullet*);

        const int   get_timer() const;
        const int   get_wave_index() const;
        const int   get_wave_count() const;

        void    draw(GPLib* gp) const;

        void    clear();
};