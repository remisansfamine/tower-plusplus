#pragma once

#include <vector>

class ResourceManager;
class Enemy;
class Tower;
class Bullet;

class EntityManager
{
    private:
        std::string m_spawn_pattern;
        const ResourceManager m_ResourceManager;
        float   m_spawn_cooldown;
        float   m_spawn_rate = 1;
        float   m_wave_timer = 10;
        unsigned int    m_spawn_index = 0;

    public:
        EntityManager(const ResourceManager&);

        ~EntityManager();

        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;

        void    update(float delta_time);

        void    spawn_enemies();

        void    createTower(Tower*);
        void    createEnemy(Enemy*);
        void    createBullet(Bullet*);

        void    destroyTower(Tower*);
        void    destroyEnemy(Enemy*);
        void    destroyBullet(Bullet*);
};