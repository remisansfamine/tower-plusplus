#pragma once

#include <vector>
#include <string>
#include "resource_manager.h"
#include "castle.h"

enum class GameState
{
    WIN,
    LOSE,
    RUNNING
};

class Enemy;
class Tower;
class Bullet;

class EntityManager
{
    private:
        GPLib* m_gp;

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

        void    spawnEnemies();

        void    clear();

    public:
        GameState   m_gameState = GameState::RUNNING;

        const ResourceManager m_resourceManager;

        std::vector<Enemy*>     m_enemies;
        std::vector<Tower*>     m_towers;
        std::vector<Bullet*>    m_bullets;

        Castle                  m_castle;

        EntityManager(const ResourceManager&, GPLib* gp);

        ~EntityManager();

        void    update(float delta_time);

        void    draw() const;

        void    createTower(Tower*);
        void    createBullet(Bullet*);

        const int   getTimer() const;
        const int   getWaveIndex() const;
        const int   getWaveCount() const;
        const unsigned int    getEnemyCount() const;
};