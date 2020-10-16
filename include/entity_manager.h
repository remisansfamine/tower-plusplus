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
        std::string m_spawnPattern;
        bool    m_isInWave = false;
        float   m_spawnCooldown;
        float   m_spawnRate = 1;
        float   m_waveTimer = 10;
        unsigned int    m_spawnIndex = 0;
        unsigned int    m_waveIndex = 1;
        unsigned int    m_waveCount = 0;

        void    destroyTower(int index);
        void    destroyEnemy(int index);
        void    destroyBullet(int index);

        void    createEnemy(Enemy*);

    public:
        GPLib* m_gp;

        const ResourceManager m_resourceManager;

        EntityManager(const ResourceManager&, GPLib* gp);

        ~EntityManager();

        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;

        Castle                  m_castle;

        void    update(float delta_time);

        void    spawnEnemies();

        void    createTower(Tower*);
        void    createBullet(Bullet*);

        const int   getTimer() const;
        const int   getWaveIndex() const;
        const int   getWaveCount() const;

        void    draw() const;

        void    clear();

        unsigned int    getEnemyCount() const;
};